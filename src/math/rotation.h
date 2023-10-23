//
// Created by q on 2023/10/18.
//

#ifndef MYSOFTWARERENDERPIPE_ROTATION_H
#define MYSOFTWARERENDERPIPE_ROTATION_H

#include "matrix.h"
#include "rm_type_names.h"

class EulerAngle {
public:
    float &roll() {
        return x;
    }

    float &pitch() {
        return y;
    }

    float &yaw() {
        return z;
    }

    Matrix4x4 rotationMatrix() const {
        float s3 = sin(x);
        float s2 = sin(y);
        float s1 = sin(z);
        float c3 = cos(x);
        float c2 = cos(y);
        float c1 = cos(z);
        return Matrix4x4{c1 * c2, c1 * s2 * s3 - c3 * s1, s1 * s3 + c1 * c3 * s2, 0,
                         c2 * s1, c1 * c3 + s1 * s2 * s3, c3 * s1 * s2 - c1 * s3, 0,
                         -s2, c2 * s3, c2 * c3, 0,
                         0, 0, 0, 1};
    }

    Matrix3x3 rotationMatrix3x3() const {
        float s3 = sin(x);
        float s2 = sin(y);
        float s1 = sin(z);
        float c3 = cos(x);
        float c2 = cos(y);
        float c1 = cos(z);
        return Matrix3x3{c1 * c2, c1 * s2 * s3 - c3 * s1, s1 * s3 + c1 * c3 * s2,
                         c2 * s1, c1 * c3 + s1 * s2 * s3, c3 * s1 * s2 - c1 * s3,
                         -s2, c2 * s3, c2 * c3};
    }

    float x, y, z;
};

#endif //MYSOFTWARERENDERPIPE_ROTATION_H
