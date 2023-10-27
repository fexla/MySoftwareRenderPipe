//
// Created by q on 2023/10/19.
//

#ifndef MYSOFTWARERENDERPIPE_SHADER_H
#define MYSOFTWARERENDERPIPE_SHADER_H


#include "color.h"
#include "camera.h"

class point_shader {
public:
    ~point_shader() = default;

    color shade() {
        return C_WHITE;
    }

};

template<typename VertexData>
class line_frag_shader {
public:
    ~line_frag_shader() = default;

    color shade(const VertexData *v1, const VertexData *v2, float t) {
        return C_WHITE;
    }

};

template<typename VertexData>
class frag_shader {
public:
    ProjectionMode projectionMode = ProjectionMode::Perspective;

    ~frag_shader() = default;

    /**
     * 根据投影模式计算片元的重心坐标
     * @param vertices 三角形顶点坐标（屏幕空间坐标系）
     * @param pos 要获取顶点坐标的片元坐标
     * @return 重心坐标
     */
    array<float, 3> getCoord(array<Vector3f, 3> vertices, Vector2f pos) {
        auto coord = barycentric_coordinates2d(pos, {
                Vector2f{vertices[0][0], vertices[0][1]},
                Vector2f{vertices[1][0], vertices[1][1]},
                Vector2f{vertices[2][0], vertices[2][1]},
        });
        if (projectionMode == ProjectionMode::Perspective) {
            array<float, 3> originDep = {vertices[0][2], vertices[1][2], vertices[2][2]};
            float depth = interpolation(originDep, coord);
            interpolation_correction(coord, originDep, depth);
        }
        return coord;
    }

    /**
     * 着色
     * @param vertexBuffer 顶点数据
     * @param coord 片元的重心坐标
     * @return 颜色
     */
    color shade(const VertexData *vertexBuffer[3], array<float, 3> coord) {
        return C_WHITE;
    }

};

#endif //MYSOFTWARERENDERPIPE_SHADER_H
