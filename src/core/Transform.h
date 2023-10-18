//
// Created by q on 2023/10/18.
//

#ifndef MYSOFTWARERENDERPIPE_TRANSFORM_H
#define MYSOFTWARERENDERPIPE_TRANSFORM_H

#include "renderer_math.h"

class Transform {
public:
    Vector3f position;
    EulerAngle rotation;

    Matrix4x4 getModelMatrix() {
        auto matrix = rotation.rotationMatrix();
        matrix[0][3] = position[0];
        matrix[1][3] = position[1];
        matrix[2][3] = position[2];
        return matrix;
    }
};

#endif //MYSOFTWARERENDERPIPE_TRANSFORM_H
