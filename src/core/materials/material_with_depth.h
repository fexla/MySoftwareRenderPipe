//
// Created by q on 2023/10/23.
//

#ifndef MYSOFTWARERENDERPIPE_MATERIAL_WITH_DEPTH_H
#define MYSOFTWARERENDERPIPE_MATERIAL_WITH_DEPTH_H


#include "renderer.h"

class show_depth : public frag_shader<DefVtxDataInPip> {
public:
    color shade(const DefVtxDataInPip *[3], float, float, float);
};

class material_with_depth : public material {
public:
    buffer2d<float> *depthBuffer;

    void renderTarget(buffer2d<color> &renderBuffer, model &model, std::vector<DefVtxDataInPip> &vector) const override;

protected:
    template<typename VertexData, typename Shader>
    std::enable_if_t<std::is_base_of_v<frag_shader<VertexData>, Shader>, void>
    shadeTarget(buffer2d<color> &renderBuffer,
                model &model,
                std::vector<VertexData> &vData,
                Shader &shader) const {
        for (int t = 0; t < model.triangles.size(); ++t) {
            auto &triangle = model.triangles[t];
            const DefVtxDataInPip *triangleVertexData[3]{
                    &vData[triangle[0]],
                    &vData[triangle[1]],
                    &vData[triangle[2]],
            };
            Vector3f vertexScreenPos[3];
            for (int j = 0; j < 3; ++j) {
                vertexScreenPos[j] = {
                        (vData[triangle[j]].clipPos[0] / 2 + 0.5f) * renderBuffer.getWidth(),
                        (vData[triangle[j]].clipPos[1] / 2 + 0.5f) * renderBuffer.getHeight(),
                        (vData[triangle[j]].clipPos[2]),
                };
            }
            rasterize_triangle(
                    &renderBuffer,
                    depthBuffer,
                    triangleVertexData,
                    vertexScreenPos,
                    shader
            );
        }
    }
};


#endif //MYSOFTWARERENDERPIPE_MATERIAL_WITH_DEPTH_H
