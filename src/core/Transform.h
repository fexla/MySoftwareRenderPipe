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
};

Matrix4x4 getModelMatrix(Transform &objectTransform) {
    auto &rotation = objectTransform.rotation;
    auto position = objectTransform.position;
    auto matrix = rotation.rotationMatrix();
    matrix[0][3] = position[0];
    matrix[1][3] = position[1];
    matrix[2][3] = position[2];
    return matrix;
}

Matrix4x4 getViewMatrix(Transform &cameraTransform) {
    auto &rotation = cameraTransform.rotation;
    auto &position = cameraTransform.position;
    Matrix4x4 matrix = {
            1, 0, 0, -position[0],
            0, 1, 0, -position[1],
            0, 0, 1, -position[2],
            0, 0, 0, 1,
    };
    return rotation.rotationMatrix().transpose() * matrix;
}

#endif //MYSOFTWARERENDERPIPE_TRANSFORM_H
