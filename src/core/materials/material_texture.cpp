//
// Created by q on 2023/10/23.
//

#include "material_texture.h"
#include "rasterization.h"

class color show_texture::shade(const DefVtxDataInPip *vertexBuffer[3],
                                float alpha,
                                float beta,
                                float gamma) {
    float depth = 1.f / (alpha / vertexBuffer[0]->dep + beta / vertexBuffer[1]->dep + gamma / vertexBuffer[2]->dep);
    auto trueCoord = interpolation_correction(
            {alpha, beta, gamma},
            {vertexBuffer[0]->dep, vertexBuffer[1]->dep, vertexBuffer[2]->dep},
            depth
    );
    float u = vertexBuffer[0]->uv[0] * trueCoord[0] +
              vertexBuffer[1]->uv[0] * trueCoord[1] +
              vertexBuffer[2]->uv[0] * trueCoord[2];
    float v = vertexBuffer[0]->uv[1] * trueCoord[0] +
              vertexBuffer[1]->uv[1] * trueCoord[1] +
              vertexBuffer[2]->uv[1] * trueCoord[2];
    if (u > 1 || u < 0 || v > 1 || v < 0) return C_RED;
    return texture->getColor(u, v);
}

void material_texture::renderTarget
        (buffer2d<color> &renderBuffer, model &model, std::vector<DefVtxDataInPip> &vData) const {
    show_texture shader{};
    shader.texture = texture;
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
