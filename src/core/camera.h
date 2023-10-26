//
// Created by q on 2023/10/20.
//

#ifndef MYSOFTWARERENDERPIPE_CAMERA_H
#define MYSOFTWARERENDERPIPE_CAMERA_H

#include "vector"

#include "renderer_math.h"
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
    float near = -0.01;
    float far = -100;

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

    std::vector<Vector4f> getEyeFieldVertices() {
        std::vector<Vector4f> vertices(8);
        if (mode == ProjectionMode::Perspective) {
            //TODO
        } else {
            vertices[0] = Vector4f{-size * aspect, size, near};
            vertices[1] = Vector4f{size * aspect, size, near};
            vertices[2] = Vector4f{-size * aspect, -size, near};
            vertices[3] = Vector4f{size * aspect, -size, near};
            vertices[4] = Vector4f{-size * aspect, size, far};
            vertices[5] = Vector4f{size * aspect, size, far};
            vertices[6] = Vector4f{-size * aspect, -size, far};
            vertices[7] = Vector4f{size * aspect, -size, far};
            auto model_mat = getModelMatrix(trans);
            for (int i = 0; i < 8; ++i) {
                vertices[i][3] = 1;
                vertices[i] = model_mat * vertices[i];
            }
            return vertices;
        }
        return {};
    }
};

#endif //MYSOFTWARERENDERPIPE_CAMERA_H
