//
// Created by q on 2023/10/18.
//

#ifndef MYSOFTWARERENDERPIPE_RASTERIZATION_H
#define MYSOFTWARERENDERPIPE_RASTERIZATION_H

#include "renderer_math.h"
#include "shader.h"

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

template<typename GraphicsBuffer, typename VertexData, typename Shader>
void shadePointInTriangle(GraphicsBuffer *buffer,
                          const VertexData *vertexBuffer[3],
                          Vector3f vertexPos[3],
                          Shader &shader,
                          Vector2f pos) {
    auto [alpha, beta, gamma] = barycentric_coordinates2d(pos, {
            Vector2f{vertexPos[0][0], vertexPos[0][1]},
            Vector2f{vertexPos[1][0], vertexPos[1][1]},
            Vector2f{vertexPos[2][0], vertexPos[2][1]},
    });
    (*buffer)[(int) pos[0]][(int) pos[1]] = shader.shade(vertexBuffer, alpha, beta, gamma);
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
    Vector3f bottom = {vertexPos[0][0], vertexPos[0][1]},
            top = {vertexPos[1][0], vertexPos[1][1]},
            midL = {vertexPos[2][0], vertexPos[2][1]},
            midR;
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
        float left = std::min(std::min(bottom[0], midL[0]), top[0]);
        float right = std::max(std::max(bottom[0], midL[0]), top[0]);
        for (int i = left; i <= right; ++i) {
//            (*buffer)[i][(int) top[1]] = shader.shade(vertexBuffer, 0, 0, 0);
            shadePointInTriangle(buffer, vertexBuffer, vertexPos, shader, {(float) i, top[1]});
        }
        return;
    }
    float kBottomTop = 1.0 * (top[1] - bottom[1]) / (top[0] - bottom[0]);
    midR = {bottom[0] + (midL[1] - bottom[1]) / kBottomTop, midL[1]};
    if (midR[0] < midL[0]) {
        std::swap(midR, midL);
    }
    if (midL[1] == bottom[1]) {
        float left = std::min(std::min(bottom[0], midL[0]), midR[0]);
        float right = std::max(std::max(bottom[0], midL[0]), midR[0]);
        for (int i = left; i <= right; ++i) {
//            (*buffer)[i][(int) midL[1]] = shader.shade(vertexBuffer, 0, 0, 0);
            shadePointInTriangle(buffer, vertexBuffer, vertexPos, shader, {(float) i, midL[1]});
        }
    } else {
        float kBottomMidLInv = 1.0 * (midL[0] - bottom[0]) / (midL[1] - bottom[1]);
        float kBottomMidRInv = 1.0 * (midR[0] - bottom[0]) / (midR[1] - bottom[1]);
        for (int y = 0; y <= midL[1] - bottom[1]; ++y) {
            float left = bottom[0] + kBottomMidLInv * y + 0.5,
                    right = bottom[0] + kBottomMidRInv * y + 0.5;
            for (int x = left; x <= right; ++x) {
//                (*buffer)[x][(int) (bottom[1] + y)] = shader.shade(vertexBuffer, 0, 0, 0);
                shadePointInTriangle(buffer, vertexBuffer, vertexPos, shader, {x, bottom[1] + y});
            }
        }
    }
    if (top[1] == bottom[1]) {
        float left = std::min(std::min(top[0], midL[0]), midR[0]);
        float right = std::max(std::max(top[0], midL[0]), midR[0]);
        for (int i = left; i <= right; ++i) {
            (*buffer)[i][(int) midL[1]] = shader.shade(vertexBuffer, 0, 0, 0);
        }
    } else {
        float kTopMidLInv = 1.0 * (midL[0] - top[0]) / (midL[1] - top[1]);
        float kTopMidRInv = 1.0 * (midR[0] - top[0]) / (midR[1] - top[1]);
        for (int y = 0; y <= top[1] - midL[1]; ++y) {
            float left = top[0] - kTopMidLInv * y + 0.5,
                    right = top[0] - kTopMidRInv * y + 0.5;
            for (int x = left; x <= right; ++x) {
//                (*buffer)[x][(int) (top[1] - y)] = shader.shade(vertexBuffer, 0, 0, 0);
                shadePointInTriangle(buffer, vertexBuffer, vertexPos, shader, {x, top[1] - y});
            }
        }
    }
}

#endif //MYSOFTWARERENDERPIPE_RASTERIZATION_H
