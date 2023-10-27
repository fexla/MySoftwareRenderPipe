//
// Created by q on 2023/10/18.
//
#include "transform.h"

Matrix4x4 getModelMatrix(const transform &objectTransform) {
    auto &rotation = objectTransform.rotation;
    auto position = objectTransform.position;
    auto matrix = rotation.rotationMatrix();
    Matrix4x4 scaleMat{
            objectTransform.scale[0], 0, 0, 0,
            0, objectTransform.scale[1], 0, 0,
            0, 0, objectTransform.scale[2], 0,
            0, 0, 0, 1
    };
    matrix = matrix * scaleMat;
    matrix[0][3] = position[0];
    matrix[1][3] = position[1];
    matrix[2][3] = position[2];
    return matrix;
}

Matrix4x4 getViewMatrix(const transform &cameraTransform) {
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
            0, 0, (far + near) / (near - far), 2 * near * far / (far - near),
            0, 0, -1, 0
    };
}

Matrix4x4 getOrthogonalProjectionMatrix(float size, float aspect, float far, float near) {
    return {
            1 / (size * aspect), 0, 0, 0,
            0, 1 / size, 0, 0,
            0, 0, 2 / (far - near), (far + near) / (near - far),
            0, 0, 0, 1
    };
}

Matrix4x4 getTranslationMatrix(Vector3f to, Vector3f from) {
    return {
            1, 0, 0, to[0] - from[0],
            0, 1, 0, to[1] - from[1],
            0, 0, 1, to[2] - from[2],
            0, 0, 0, 1,
    };
}

Matrix4x4 getScaleMatrix(Vector3f scale) {
    return {
            scale[0], 0, 0, 0,
            0, scale[1], 0, 0,
            0, 0, scale[2], 0,
            0, 0, 0, 1
    };
}
