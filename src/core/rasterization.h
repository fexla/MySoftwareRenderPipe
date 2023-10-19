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
                Vector2i pos,
                Shader &shader) {
    (*buffer)[pos[0]][pos[1]] = shader.shade();
}

/**
 * Bresenham画线算法
 * @tparam GraphicsBuffer 画布类型
 * @tparam VertexData 顶点数据类型
 * @tparam Shader 着色器
 * @param buffer 画布
 * @param start 起点坐标
 * @param end 终点坐标
 * @param v1Data 起点数据
 * @param v2Data 终点数据
 * @param shader 着色器
 * @return void
 */
template<typename GraphicsBuffer, typename VertexData, typename Shader>
std::enable_if_t<std::is_base_of_v<line_frag_shader<VertexData>, Shader>, void>
rasterize_line(GraphicsBuffer *buffer,
               Vector2i start,
               Vector2i end,
               const VertexData *v1Data,
               const VertexData *v2Data,
               Shader &shader) {
    if (start == end) {
        (*buffer)[start[0]][start[1]] = shader.shade(v1Data, v2Data, 1);
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
            (*buffer)[start[0] + i][y] = shader.shade(v1Data, v2Data, t);
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
            (*buffer)[x][start[1] + i] = shader.shade(v1Data, v2Data, t);
            if (bFlip) {
                t -= yDiffInv;
            } else {
                t += yDiffInv;
            }
        }
    }
}
#endif //MYSOFTWARERENDERPIPE_RASTERIZATION_H
