//
// Created by q on 2023/10/23.
//
#include "material_lambert.h"

class color lambert_shader::shade(const DefVtxDataInPip *vertexBuffer[3],
                                  float alpha,
                                  float beta,
                                  float gamma) {
    float depth = 1.f / (alpha / vertexBuffer[0]->dep + beta / vertexBuffer[1]->dep + gamma / vertexBuffer[2]->dep);
    auto trueCoord = interpolation_correction(
            {alpha, beta, gamma},
            {vertexBuffer[0]->dep, vertexBuffer[1]->dep, vertexBuffer[2]->dep},
            depth
    );
    Vector3f norm =
            vertexBuffer[0]->norm * trueCoord[0] +
            vertexBuffer[1]->norm * trueCoord[1] +
            vertexBuffer[2]->norm * trueCoord[2];
    norm = *dir2world * norm;
    norm.normalize();

    float intensity = 0.3;
    for (auto &l: *directionLights) {
        intensity +=
                std::max(-dot(l.direction.normalize(), norm), 0.f) *
                l.intensity;
    }
    intensity = std::min(intensity, 1.f);
    return C_WHITE * intensity;
}

void material_lambert::renderTarget
        (buffer2d<color> &renderBuffer, model &model, std::vector<DefVtxDataInPip> &vData) const {
    lambert_shader shader{};
    shader.directionLights = directionLights;
    shader.dir2world = dir2world;
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
