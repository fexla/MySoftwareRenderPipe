//
// Created by q on 2023/10/18.
//

#ifndef MYSOFTWARERENDERPIPE_TRANSFORM_H
#define MYSOFTWARERENDERPIPE_TRANSFORM_H

#include "cmath"

#include "renderer_math.h"

class transform {
public:
    transform() : position{0}, rotation{}, scale{1, 1, 1} {}

    transform(const Vector3f &position, const EulerAngle &rotation) :
            position(position), rotation(rotation), scale{1, 1, 1} {}

    transform(const Vector3f &position, const Vector3f &scale, const EulerAngle &rotation) :
            position(position), scale(scale), rotation(rotation) {}

    Vector3f position;
    EulerAngle rotation;
    Vector3f scale;
};

Matrix4x4 getModelMatrix(const transform &objectTransform);

Matrix4x4 getViewMatrix(const transform &cameraTransform);

Matrix4x4 getPerspectiveProjectionMatrix(float fov, float aspect, float far, float near);

Matrix4x4 getOrthogonalProjectionMatrix(float size, float aspect, float far, float near);

/**
 * 获得平移矩阵
 * @return
 */
Matrix4x4 getTranslationMatrix(Vector3f to, Vector3f from = Vector3f{});

/**
 * 获得缩放矩阵
 * @return
 */
Matrix4x4 getScaleMatrix(Vector3f scale);

#endif //MYSOFTWARERENDERPIPE_TRANSFORM_H
