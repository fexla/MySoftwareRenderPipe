//
// Created by q on 2023/10/23.
//

#ifndef MYSOFTWARERENDERPIPE_MATERIAL_WITH_DEPTH_H
#define MYSOFTWARERENDERPIPE_MATERIAL_WITH_DEPTH_H


#include "renderer.h"

class show_depth : public frag_shader<DefVtxDataInPip> {
public:
    color shade(const DefVtxDataInPip *[3], float, float, float);
};

class material_with_depth : public material {
public:
    buffer2d<float> *depthBuffer;

    void renderTarget(buffer2d<color> &renderBuffer, model &model, std::vector<DefVtxDataInPip> &vector) const override;
};


#endif //MYSOFTWARERENDERPIPE_MATERIAL_WITH_DEPTH_H
