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

Matrix4x4 getModelMatrix(const Transform &objectTransform);

Matrix4x4 getViewMatrix(const Transform &cameraTransform);

Matrix4x4 getPerspectiveProjectionMatrix(float fov, float aspect, float far, float near);

#endif //MYSOFTWARERENDERPIPE_TRANSFORM_H
