//
// Created by q on 2023/10/19.
//

#ifndef MYSOFTWARERENDERPIPE_UTILITY_H
#define MYSOFTWARERENDERPIPE_UTILITY_H

#include "array"
#include "rm_type_names.h"

using std::array;

inline bool isTriangleClockwise(array<Vector2f, 3> triangle) {
    auto v1 = triangle[1] - triangle[0];
    auto v2 = triangle[2] - triangle[0];
    return v1.cross(v2) < 0;
}

template<typename DataType>
inline std::enable_if_t<std::is_arithmetic_v<DataType>, DataType>
clamp(DataType a, DataType min, DataType max) {
    return std::min(max, std::max(a, min));
}

#endif //MYSOFTWARERENDERPIPE_UTILITY_H
