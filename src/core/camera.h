//
// Created by q on 2023/10/20.
//

#ifndef MYSOFTWARERENDERPIPE_CAMERA_H
#define MYSOFTWARERENDERPIPE_CAMERA_H

#include <cmath>

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
//        if (1) {
        if (mode == ProjectionMode::Perspective) {
            Vector3f dir[4];
            float angle = fov / 2;
            float height = std::tan(angle);
            float width = height * aspect;
            dir[0] = Vector3f{width, height, 1};
            dir[1] = Vector3f{-width, height, 1};
            dir[2] = Vector3f{width, -height, 1};
            dir[3] = Vector3f{-width, -height, 1};
            vertices[0] = (dir[0] * near).resize<4>(1);
            vertices[1] = (dir[1] * near).resize<4>(1);
            vertices[2] = (dir[2] * near).resize<4>(1);
            vertices[3] = (dir[3] * near).resize<4>(1);
            vertices[4] = (dir[0] * far).resize<4>(1);
            vertices[5] = (dir[1] * far).resize<4>(1);
            vertices[6] = (dir[2] * far).resize<4>(1);
            vertices[7] = (dir[3] * far).resize<4>(1);
            auto model_mat = getModelMatrix(trans);
            for (int i = 0; i < 8; ++i) {
                vertices[i] = model_mat * vertices[i];
            }
            return vertices;
        }
        else {
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
