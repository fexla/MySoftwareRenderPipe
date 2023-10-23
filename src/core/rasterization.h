//
// Created by q on 2023/10/18.
//

#ifndef MYSOFTWARERENDERPIPE_RASTERIZATION_H
#define MYSOFTWARERENDERPIPE_RASTERIZATION_H

#include "renderer_math.h"
#include "shader.h"
#include "utility.h"

template<typename GraphicsBuffer, typename Shader=point_shader>
inline std::enable_if_t<std::is_base_of_v<point_shader, Shader>, void>
rasterize_point(GraphicsBuffer *buffer,
                Vector3f pos,
                Shader &shader) {
    (*buffer)[(int) (pos[0] + 0.5)][int(pos[1] + 0.5)] = shader.shade();
}

/**
 * Bresenham画线算法
 * @tparam GraphicsBuffer 画布类型
 * @tparam VertexData 顶点数据类型
 * @tparam Shader 着色器
 * @param buffer 画布
 * @param start 起点坐标（z分量为深度值）
 * @param end 终点坐标（z分量为深度值）
 * @param v1Data 起点数据
 * @param v2Data 终点数据
 * @param shader 着色器
 * @return void
 */
template<typename GraphicsBuffer, typename VertexData, typename Shader>
std::enable_if_t<std::is_base_of_v<line_frag_shader<VertexData>, Shader>, void>
rasterize_line(GraphicsBuffer *buffer,
               Vector3f start,
               Vector3f end,
               const VertexData *v1Data,
               const VertexData *v2Data,
               Shader &shader) {
    if (start == end) {
        (*buffer)[(int) (start[0] + 0.5)][(int) (start[1] + 0.5)] = shader.shade(v1Data, v2Data, 1);
        return;
    }
    //计算起点终点在x轴和y轴上的距离
    int xDiff = abs(end[0] - start[0]);
    int yDiff = abs(end[1] - start[1]);
    if (yDiff <= xDiff) {
        bool bFlip = 0;
        float t = 0;
        if (start[0] > end[0]) {
            std::swap(start, end);
            bFlip = 1;
            t = 1;
        }
        float k = 1.0 * (end[1] - start[1]) / xDiff;
        float xDiffInv = 1.0 / xDiff;
        for (int i = 0; i <= xDiff; ++i) {
            int y = start[1] + i * k + 0.5;
            (*buffer)[(int) (start[0] + i)][y] = shader.shade(v1Data, v2Data, t);
            if (bFlip) {
                t -= xDiffInv;
            } else {
                t += xDiffInv;
            }
        }
    } else {
        bool bFlip = 0;
        float t = 0;
        if (start[1] > end[1]) {
            std::swap(start, end);
            bFlip = 1;
            t = 1;
        }
        float k = 1.0 * (end[0] - start[0]) / yDiff;
        float yDiffInv = 1.0 / yDiff;
        for (int i = 0; i <= yDiff; ++i) {
            int x = start[0] + i * k + 0.5;
            (*buffer)[x][(int) (start[1] + i)] = shader.shade(v1Data, v2Data, t);
            if (bFlip) {
                t -= yDiffInv;
            } else {
                t += yDiffInv;
            }
        }
    }
}

template<typename GraphicsBuffer, typename DepthBuffer = void, typename VertexData, typename Shader>
void shadePointInTriangle(GraphicsBuffer *buffer,
                          DepthBuffer *depthBuffer,
                          const VertexData *vertexBuffer[3],
                          Vector3f vertexPos[3],
                          Shader &shader,
                          Vector2f realPos,
                          Vector2i pixelPos) {
    auto [alpha, beta, gamma] = barycentric_coordinates2d(realPos, {
            Vector2f{vertexPos[0][0], vertexPos[0][1]},
            Vector2f{vertexPos[1][0], vertexPos[1][1]},
            Vector2f{vertexPos[2][0], vertexPos[2][1]},
    });
    unsigned int x = pixelPos[0];
    unsigned int y = pixelPos[1];
    if constexpr (std::is_base_of_v<buffer2d<color>, GraphicsBuffer>) {
        if (x >= buffer->getWidth() || y >= buffer->getHeight()) {
            return;
        }
    }
    float depth = 1.f / (alpha / vertexPos[0][2] + beta / vertexPos[1][2] + gamma / vertexPos[2][2]);
    if (depth >= 0) {
        return;
    }
    if constexpr (!std::is_same_v<void, DepthBuffer>) {
        if ((*depthBuffer)[x][y] > depth) {
            (*buffer)[x][y] = shader.shade(vertexBuffer, alpha, beta, gamma);
            (*depthBuffer)[x][y] = depth;
        }
    } else {
        (*buffer)[x][y] = shader.shade(vertexBuffer, alpha, beta, gamma);
    }
}

/**
 * 光栅化三角形
 * @tparam GraphicsBuffer 画布类型
 * @tparam DepthBuffer 深度缓冲类型
 * @tparam VertexData 顶点数据类型
 * @tparam Shader 着色器
 * @param buffer 画布
 * @param vertexBuffer 顶点数据
 * @param vertexPos 顶点位置（z分量为深度值）
 * @param shader 着色器
 * @return
 */
template<typename GraphicsBuffer, typename DepthBuffer = void, typename VertexData, typename Shader>
std::enable_if_t<std::is_base_of_v<frag_shader<VertexData>, Shader>, void>
rasterize_triangle(GraphicsBuffer *buffer,
                   DepthBuffer *depthBuffer,
                   const VertexData *vertexBuffer[3],
                   Vector3f vertexPos[3],
                   Shader &shader) {
    Vector2f bottom = {vertexPos[0][0], vertexPos[0][1]},
            top = {vertexPos[1][0], vertexPos[1][1]},
            midL = {vertexPos[2][0], vertexPos[2][1]},
            midR;

    //背面剔除
    if (isTriangleClockwise({bottom, top, midL})) {
        return;
    }

    //将三角形三个点按y值排序
    if (midL[1] > top[1]) {
        std::swap(midL, top);
    }
    if (bottom[1] > midL[1]) {
        std::swap(midL, bottom);
    }
    if (midL[1] > top[1]) {
        std::swap(midL, top);
    }

    if (top[1] == bottom[1]) {
        return;
    }
    float kBottomTop = 1.0 * (top[1] - bottom[1]) / (top[0] - bottom[0]);
    midR = {bottom[0] + (midL[1] - bottom[1]) / kBottomTop, midL[1]};
    if (midR[0] < midL[0]) {
        std::swap(midR, midL);
    }
    if (midL[1] != bottom[1]) {
        float kBottomMidLInv = 1.0 * (midL[0] - bottom[0]) / (midL[1] - bottom[1]);
        float kBottomMidRInv = 1.0 * (midR[0] - bottom[0]) / (midR[1] - bottom[1]);
        float curY, endY;
        curY = floor(bottom[1] + 0.5) + 0.5;
        endY = ceil(midL[1] - 0.5) + 0.5;
        while (curY < endY) {
            float deltaY = curY - bottom[1];
            float left = bottom[0] + kBottomMidLInv * deltaY,
                    right = bottom[0] + kBottomMidRInv * deltaY;
            float curX, endX;
            curX = floor(left + 0.5) + 0.5;
            endX = ceil(right + 0.5) - 0.5;
            while (curX < endX) {
                shadePointInTriangle(buffer, depthBuffer, vertexBuffer, vertexPos, shader,
                                     {curX, curY}, {curX, curY});
                curX += 1;
            }
            curY += 1;
        }
    }
    if (midL[1] != top[1]) {
        float kTopMidLInv = 1.0 * (midL[0] - top[0]) / (midL[1] - top[1]);
        float kTopMidRInv = 1.0 * (midR[0] - top[0]) / (midR[1] - top[1]);
        float curY, endY;
        curY = floor(midL[1] + 0.5) + 0.5;
        endY = ceil(top[1] + 0.5) - 0.5;
        while (curY <= endY) {
            float deltaY = curY - top[1];
            float left = top[0] + kTopMidLInv * deltaY,
                    right = top[0] + kTopMidRInv * deltaY;
            float curX, endX;
            curX = floor(left + 0.5) + 0.5;
            endX = ceil(right + 0.5) - 0.5;
            while (curX < endX) {
                shadePointInTriangle(buffer, depthBuffer, vertexBuffer, vertexPos, shader,
                                     {curX, curY}, {curX, curY});
                curX += 1;
            }
            curY += 1;
        }
    }
}

/**
 * 光栅化三角形
 * @tparam GraphicsBuffer 画布类型
 * @tparam VertexData 顶点数据类型
 * @tparam Shader 着色器
 * @param buffer 画布
 * @param vertexBuffer 顶点数据
 * @param vertexPos 顶点位置（z分量为深度值）
 * @param shader 着色器
 * @return
 */
template<typename GraphicsBuffer, typename VertexData, typename Shader>
std::enable_if_t<std::is_base_of_v<frag_shader<VertexData>, Shader>, void>
rasterize_triangle(GraphicsBuffer *buffer,
                   const VertexData *vertexBuffer[3],
                   Vector3f vertexPos[3],
                   Shader &shader) {
    rasterize_triangle<GraphicsBuffer, void, VertexData, Shader>
            (buffer, nullptr, vertexBuffer, vertexPos, shader);
}

#endif //MYSOFTWARERENDERPIPE_RASTERIZATION_H
