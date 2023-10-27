//
// Created by q on 2023/10/23.
//

#ifndef MYSOFTWARERENDERPIPE_MATERIAL_TEXTURE_H
#define MYSOFTWARERENDERPIPE_MATERIAL_TEXTURE_H


#include "buffer.h"
#include "color.h"
#include "model.h"
#include "renderer.h"
#include "material_with_depth.h"

class show_texture : public frag_shader<DefVtxDataInPip> {
public:
    color shade(const DefVtxDataInPip *[3], array<float, 3> coord);

    Texture *texture;
};

class material_texture : public material_with_depth {
public:
    using material_with_depth::depthBuffer;
    Texture *texture{};

    void renderTarget(buffer2d<color> &renderBuffer, model &model, std::vector<DefVtxDataInPip> &vector) const override;

};


#endif //MYSOFTWARERENDERPIPE_MATERIAL_TEXTURE_H
