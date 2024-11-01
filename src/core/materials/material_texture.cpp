//
// Created by q on 2023/10/23.
//

#include "material_texture.h"
#include "light_with_shadow.h"

class color show_texture::shade(const DefVtxDataInPip *vertexBuffer[3], std::array<float, 3> coord) {
    float u = vertexBuffer[0]->uv[0] * coord[0] +
              vertexBuffer[1]->uv[0] * coord[1] +
              vertexBuffer[2]->uv[0] * coord[2];
    float v = vertexBuffer[0]->uv[1] * coord[0] +
              vertexBuffer[1]->uv[1] * coord[1] +
              vertexBuffer[2]->uv[1] * coord[2];
    if(u > 1 || u < 0 || v > 1 || v < 0) return C_RED;


    float intensity = 0.3;
    if(directionLights) {
        Vector3f norm = vertexBuffer[0]->norm * coord[0] +
                        vertexBuffer[1]->norm * coord[1] +
                        vertexBuffer[2]->norm * coord[2];
        Vector4f wpos = vertexBuffer[0]->worldPos * coord[0] +
                        vertexBuffer[1]->worldPos * coord[1] +
                        vertexBuffer[2]->worldPos * coord[2];
        norm = *dir2world * norm;
        norm.normalize();
        for (auto &l: *directionLights) {
            float curIntensity = std::max(-dot(l->direction.normalize(), norm), 0.f) * l->intensity;
            if(auto shadowLight = dynamic_cast<light_with_shadow *>(l.get())) {
                curIntensity *= 1 - shadowLight->getShadow(wpos);
            }
            intensity += curIntensity;
        }
    }
    intensity = std::min(intensity, 1.f);
    color c = texture->getColor(u, v) * intensity;
    c.a = 1;
    return c;
}

void material_texture::renderTarget
        (buffer2d<color> &renderBuffer, model &model, std::vector<DefVtxDataInPip> &vData) const {
    show_texture shader{};
    shader.texture = texture;
    shader.dir2world = dir2world;
    shader.directionLights = directionLights;
    shadeTarget(renderBuffer, model, vData, shader);
}
