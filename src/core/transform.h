//
// Created by q on 2023/10/18.
//

#ifndef MYSOFTWARERENDERPIPE_TRANSFORM_H
#define MYSOFTWARERENDERPIPE_TRANSFORM_H

#include "renderer_math.h"
#include "cmath"

class transform {
public:
    transform() : position{0}, rotation{0} {}

    transform(const Vector3f &position, const EulerAngle &rotation) : position(position), rotation(rotation) {}

    Vector3f position;
    EulerAngle rotation;
};

Matrix4x4 getModelMatrix(const transform &objectTransform);

Matrix4x4 getViewMatrix(const transform &cameraTransform);

Matrix4x4 getPerspectiveProjectionMatrix(float fov, float aspect, float far, float near);

#endif //MYSOFTWARERENDERPIPE_TRANSFORM_H
