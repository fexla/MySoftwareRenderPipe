//
// Created by q on 2023/10/19.
//

#ifndef MYSOFTWARERENDERPIPE_UTILITY_H
#define MYSOFTWARERENDERPIPE_UTILITY_H

#include "array"
#include "renderer_math.h"

using std::array;

inline bool isTriangleClockwise(array<Vector2f, 3> triangle) {
    auto v1 = triangle[1] - triangle[0];
    auto v2 = triangle[2] - triangle[0];
    return v1.cross(v2) < 0;
}

#endif //MYSOFTWARERENDERPIPE_UTILITY_H
