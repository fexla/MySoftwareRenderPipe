//
// Created by q on 2023/10/23.
//

#include "material_with_depth.h"
#include "iostream"

class color show_depth::shade(const DefVtxDataInPip *vertexBuffer[3],
                              float alpha,
                              float beta,
                              float gamma) {
    color c{0, 0, 0};
    float depth = 1.f / (alpha / vertexBuffer[0]->dep + beta / vertexBuffer[1]->dep + gamma / vertexBuffer[2]->dep);
    float gray = log10(depth);
    gray -= floor(gray);
    gray = std::min(gray, 1.f);
    c = {gray, gray, gray, 1};
    return c;
}

void material_with_depth::renderTarget(buffer2d<color> &renderBuffer, model &model,
                                       std::vector<DefVtxDataInPip> &vData) const {
    show_depth shader;
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
