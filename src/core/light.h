//
// Created by q on 2023/10/23.
//

#ifndef MYSOFTWARERENDERPIPE_LIGHT_H
#define MYSOFTWARERENDERPIPE_LIGHT_H

#include "renderer_math.h"

/**
 * 平行光
 */
struct direction_light {
    Vector3f direction;
    float intensity;
};

#endif //MYSOFTWARERENDERPIPE_LIGHT_H
