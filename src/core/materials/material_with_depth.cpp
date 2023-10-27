//
// Created by q on 2023/10/23.
//

#include "material_with_depth.h"

#include "iostream"

class color show_depth::shade(const DefVtxDataInPip *vertexBuffer[3], std::array<float, 3> coord) {
    color c{0, 0, 0};
    float depth = interpolation({vertexBuffer[0]->dep, vertexBuffer[1]->dep, vertexBuffer[2]->dep}, coord);
    float gray = log10(depth);
    gray -= floor(gray);
    gray = std::min(gray, 1.f);
    c = {gray, gray, gray, 1};
    return c;
}

void material_with_depth::renderTarget
        (buffer2d<color> &renderBuffer, model &model, std::vector<DefVtxDataInPip> &vData) const {
    show_depth shader;
    shadeTarget(renderBuffer, model, vData, shader);
}
