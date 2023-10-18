//
// Created by q on 2023/10/18.
//

#ifndef MYSOFTWARERENDERPIPE_VIEWPOINT_H
#define MYSOFTWARERENDERPIPE_VIEWPOINT_H

#include "Transform.h"

class ViewPoint {
public:
    Transform transform;

    Matrix4x4 getViewMatrix() {
        auto &rotation = transform.rotation;
        auto &position = transform.position;
        Matrix4x4 matrix = {
                1, 0, 0, -position[0],
                0, 1, 0, -position[1],
                0, 0, 1, -position[2],
                0, 0, 0, 1,
        };
        return rotation.rotationMatrix().transpose() * matrix;
    }
};

#endif //MYSOFTWARERENDERPIPE_VIEWPOINT_H
