//
// Created by q on 2023/10/23.
//

#ifndef MYSOFTWARERENDERPIPE_MATERIAL_LAMBERT_H
#define MYSOFTWARERENDERPIPE_MATERIAL_LAMBERT_H

#include "vector"
#include "memory"

#include "buffer.h"
#include "model.h"
#include "renderer.h"
#include "material_with_depth.h"
#include "light.h"

class lambert_shader : public frag_shader<DefVtxDataInPip> {
public:
    color shade(const DefVtxDataInPip *[3], array<float, 3> coord);

    std::vector<std::unique_ptr<direction_light>> *directionLights;

    Matrix3x3 *dir2world;
};

class material_lambert : public material_with_depth {
public:
    using material_with_depth::depthBuffer;

    void renderTarget(buffer2d<color> &renderBuffer, model &model, std::vector<DefVtxDataInPip> &vector) const override;
};

#endif //MYSOFTWARERENDERPIPE_MATERIAL_LAMBERT_H
