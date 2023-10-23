//
// Created by q on 2023/10/18.
//

#ifndef MYSOFTWARERENDERPIPE_TRANSFORM_H
#define MYSOFTWARERENDERPIPE_TRANSFORM_H

#include "renderer_math.h"
#include "cmath"

class transform {
public:
    transform() : position{0}, rotation{0}, scale{1, 1, 1} {}

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

#endif //MYSOFTWARERENDERPIPE_TRANSFORM_H
