//
// Created by q on 2023/10/23.
//
#include "material_lambert.h"
#include "light_with_shadow.h"

class color lambert_shader::shade(const DefVtxDataInPip *vertexBuffer[3], array<float, 3> coord) {
    Vector3f norm = vertexBuffer[0]->norm * coord[0] +
                    vertexBuffer[1]->norm * coord[1] +
                    vertexBuffer[2]->norm * coord[2];
    Vector4f wpos = vertexBuffer[0]->worldPos * coord[0] +
                    vertexBuffer[1]->worldPos * coord[1] +
                    vertexBuffer[2]->worldPos * coord[2];
    norm = *dir2world * norm;
    norm.normalize();

    float intensity = 0.3;
    for (auto &l: *directionLights) {
        float curIntensity = std::max(-dot(l->direction.normalize(), norm), 0.f) * l->intensity;
        if (auto shadowLight = dynamic_cast<light_with_shadow *>(l.get())) {
            curIntensity *= 1 - shadowLight->getShadow(wpos);
        }
        intensity += curIntensity;
    }
    intensity = std::min(intensity, 1.f);
    return C_WHITE * intensity;
}

void material_lambert::renderTarget
        (buffer2d<color> &renderBuffer, model &model, std::vector<DefVtxDataInPip> &vData) const {
    lambert_shader shader{};
    shader.directionLights = directionLights;
    shader.dir2world = dir2world;
    shadeTarget(renderBuffer, model, vData, shader);
}
