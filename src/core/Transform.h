//
// Created by q on 2023/10/18.
//

#ifndef MYSOFTWARERENDERPIPE_TRANSFORM_H
#define MYSOFTWARERENDERPIPE_TRANSFORM_H

#include "renderer_math.h"
#include "cmath"

class Transform {
public:
    Vector3f position;
    EulerAngle rotation;
};

Matrix4x4 getModelMatrix(const Transform &objectTransform) {
    auto &rotation = objectTransform.rotation;
    auto position = objectTransform.position;
    auto matrix = rotation.rotationMatrix();
    matrix[0][3] = position[0];
    matrix[1][3] = position[1];
    matrix[2][3] = position[2];
    return matrix;
}

Matrix4x4 getViewMatrix(const Transform &cameraTransform) {
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

Matrix4x4 getPerspectiveProjectionMatrix(float fov, float aspect, float far, float near) {
    fov /= 2;
    return {
            1 / tan(fov) / aspect, 0, 0, 0,
            0, 1 / tanh(fov), 0, 0,
            0, 0, (far + near) / (far - near), -2 * near * far / (far - near),
            0, 0, -1, 0
    };
}

#endif //MYSOFTWARERENDERPIPE_TRANSFORM_H
