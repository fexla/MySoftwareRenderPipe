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

void material_with_depth::renderTarget
        (buffer2d<color> &renderBuffer, model &model, std::vector<DefVtxDataInPip> &vData) const {
    show_depth shader;
    shadeTarget(renderBuffer, model, vData, shader);
}
