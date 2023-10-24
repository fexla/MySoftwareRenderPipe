//
// Created by q on 2023/10/20.
//

#ifndef MYSOFTWARERENDERPIPE_CAMERA_H
#define MYSOFTWARERENDERPIPE_CAMERA_H

#include "transform.h"

enum class ProjectionMode {
    Perspective, Orthogonal
};

struct camera {
    transform trans;
    ProjectionMode mode = ProjectionMode::Perspective;
    //fov in radius
    union {
        float fov = 0.25 * M_PI;
        float size;
    };
    float aspect = 1920.0 / 1080.0;
    float near = 0.01;
    float far = 100;

    auto getViewMatrix() const {
        return ::getViewMatrix(trans);
    }

    auto getPerspectiveProjectionMatrix() const {
        return ::getPerspectiveProjectionMatrix(fov, aspect, far, near);
    }

    auto getOrthogonalProjectionMatrix() const {
        return ::getOrthogonalProjectionMatrix(size, aspect, far, near);
    }

    auto getProjectionMatrix() const {
        if (mode == ProjectionMode::Perspective) {
            return getPerspectiveProjectionMatrix();
        } else if (mode == ProjectionMode::Orthogonal) {
            return getOrthogonalProjectionMatrix();
        }
    };
};

#endif //MYSOFTWARERENDERPIPE_CAMERA_H
