//
// Created by q on 2023/10/18.
//

#ifndef MYSOFTWARERENDERPIPE_ROTATION_H
#define MYSOFTWARERENDERPIPE_ROTATION_H

#include "matrix.h"
#include "rm_type_names.h"

class EulerAngle {
public:
    EulerAngle() : x(0), y(0), z(0) {}

    EulerAngle(float x, float y, float z) : x(x), y(y), z(z) {}

    float &roll() {
        return x;
    }

    float &pitch() {
        return y;
    }

    float &yaw() {
        return z;
    }

    /**
     * 外旋顺序：X-Y-Z
     * @return 旋转矩阵
     */
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

inline double vec2Angle(double x, double y) {
    double lensq = x * x + y * y;
    if (lensq == 0)return 0;
    double angle = acos(x / sqrt(lensq));
    return y > 0 ? angle : (2 * M_PI - angle);
}

inline EulerAngle vec2Euler(Vector3f vec) {
    vec.normalize();
    double x = vec[0], y = vec[1], z = vec[2];
    double vec2len = sqrt(x * x + y * y);
    float ry = acos(vec2len);
    if (z > 0)ry = 2 * (float) M_PI - ry;
    float rz = vec2Angle(x, y) - vec2Angle(vec2len, 0);
    return {0, ry, rz};
}

#endif //MYSOFTWARERENDERPIPE_ROTATION_H
