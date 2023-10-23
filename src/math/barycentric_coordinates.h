//
// Created by q on 2023/10/19.
//

#ifndef MYSOFTWARERENDERPIPE_BARYCENTRIC_COORDINATES_H
#define MYSOFTWARERENDERPIPE_BARYCENTRIC_COORDINATES_H

#include "array"
#include "utility.h"
#include "rm_type_names.h"

using std::array;

inline array<float, 3> barycentric_coordinates2d(Vector2f pos, array<Vector2f, 3> triangle) {
    float beta, gamma;
    beta = ((pos[1] - triangle[0][1]) * (triangle[2][0] - triangle[0][0]) -
            (pos[0] - triangle[0][0]) * (triangle[2][1] - triangle[0][1])) /
           ((triangle[1][1] - triangle[0][1]) * (triangle[2][0] - triangle[0][0]) -
            (triangle[1][0] - triangle[0][0]) * (triangle[2][1] - triangle[0][1]));
    gamma = ((pos[1] - triangle[0][1]) * (triangle[1][0] - triangle[0][0]) -
             (pos[0] - triangle[0][0]) * (triangle[1][1] - triangle[0][1])) /
            ((triangle[2][1] - triangle[0][1]) * (triangle[1][0] - triangle[0][0]) -
             (triangle[2][0] - triangle[0][0]) * (triangle[1][1] - triangle[0][1]));
    return {1 - beta - gamma, beta, gamma};
}

inline array<float, 3> interpolation_correction(
        const array<float, 3> &coord, const array<float, 3> &dep, float trueDep) {
    return {coord[0] * trueDep / dep[0], coord[1] * trueDep / dep[1], coord[2] * trueDep / dep[2]};
}

#endif //MYSOFTWARERENDERPIPE_BARYCENTRIC_COORDINATES_H
