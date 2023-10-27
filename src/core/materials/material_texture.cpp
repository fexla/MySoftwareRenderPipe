//
// Created by q on 2023/10/23.
//

#include "material_texture.h"
#include "rasterization.h"

class color show_texture::shade(const DefVtxDataInPip *vertexBuffer[3], array<float, 3> coord) {
    float u = vertexBuffer[0]->uv[0] * coord[0] +
              vertexBuffer[1]->uv[0] * coord[1] +
              vertexBuffer[2]->uv[0] * coord[2];
    float v = vertexBuffer[0]->uv[1] * coord[0] +
              vertexBuffer[1]->uv[1] * coord[1] +
              vertexBuffer[2]->uv[1] * coord[2];
    if (u > 1 || u < 0 || v > 1 || v < 0) return C_RED;
    return texture->getColor(u, v);
}

void material_texture::renderTarget
        (buffer2d<color> &renderBuffer, model &model, std::vector<DefVtxDataInPip> &vData) const {
    show_texture shader{};
    shader.texture = texture;
    shadeTarget(renderBuffer, model, vData, shader);
}
