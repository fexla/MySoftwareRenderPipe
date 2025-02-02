//
// Created by q on 2023/10/26.
//

#ifndef MYSOFTWARERENDERPIPE_MATERIAL_H
#define MYSOFTWARERENDERPIPE_MATERIAL_H

#include <memory>
#include "bitset"

#include "buffer.h"
#include "light.h"
#include "model.h"
#include "rasterization.h"
#include "renderer_math.h"
#include "shader.h"

struct vertex_wpos_cpos_norm_uv_dep {
    Vector4f worldPos;
    Vector4f clipPos;
    Normal norm;
    Texcoord uv;
    float dep;
};

//默认下渲染管线中的顶点数据类型
using DefVtxDataInPip = vertex_wpos_cpos_norm_uv_dep;

class material {
public:
    virtual void renderTarget(buffer2d<color> &, model &, std::vector<DefVtxDataInPip> &) const;

    mutable ProjectionMode projectionMode;
    mutable Matrix4x4 *obj2world;
    mutable Matrix3x3 *dir2world;
    mutable std::vector<std::unique_ptr<direction_light>> *directionLights;
protected:
    template<typename VertexData, typename Shader>
    std::enable_if_t<std::is_base_of_v<frag_shader<VertexData>, Shader>, void>
    shadeTarget(buffer2d<color>
                &renderBuffer,
                model &model,
                std::vector<VertexData>
                &vData,
                Shader &shader
    ) const {
        shader.projectionMode = projectionMode;
        for (int t = 0; t < model.triangles.size(); ++t) {
            auto &triangle = model.triangles[t];
            const DefVtxDataInPip *triangleVertexData[3]{
                    &vData[triangle[0]],
                    &vData[triangle[1]],
                    &vData[triangle[2]],
            };
            std::bitset<6> pointOutOfBound[3];
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    pointOutOfBound[i][j * 2] = triangleVertexData[i]->clipPos[j] > 1;
                    pointOutOfBound[i][j * 2 + 1] = triangleVertexData[i]->clipPos[j] < -1;
                }
            }
            if ((pointOutOfBound[0] & pointOutOfBound[1] & pointOutOfBound[2]).any()) {
                continue;
            }
            //背面剔除
            if (isTriangleClockwise(
                    {
                            Vector2f{triangleVertexData[0]->clipPos[0], triangleVertexData[0]->clipPos[1]},
                            Vector2f{triangleVertexData[1]->clipPos[0], triangleVertexData[1]->clipPos[1]},
                            Vector2f{triangleVertexData[2]->clipPos[0], triangleVertexData[2]->clipPos[1]},
                    })) {
                continue;
            }
            std::array<Vector3f, 3> vertexScreenPos;
            for (int j = 0; j < 3; ++j) {
                vertexScreenPos[j] = {
                        (vData[triangle[j]].clipPos[0] / 2 + 0.5f) * renderBuffer.getWidth(),
                        (vData[triangle[j]].clipPos[1] / 2 + 0.5f) * renderBuffer.getHeight(),
                        (vData[triangle[j]].clipPos[2]),
                };
            }
            rasterize_triangle(
                    &renderBuffer,
                    triangleVertexData,
                    vertexScreenPos,
                    shader
            );
        }
    }
};

const material DEFAULT_MATERIAL{};
#endif //MYSOFTWARERENDERPIPE_MATERIAL_H
