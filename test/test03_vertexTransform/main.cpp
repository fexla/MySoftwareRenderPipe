//
// Created by q on 2023/10/18.
//
#include "renderer_math.h"
#include "Transform.h"

const float PI = 3.1415926535898;

int main() {
    Transform transform1{{0,                                   0, 0},
                         {static_cast<float>(45.0 / 180 * PI), 0, 0}};
    Transform transform2{{3,                                   5, 0},
                         {static_cast<float>(45.0 / 180 * PI), 0, 0}};
    Vector4f pos{1, 1, 1, 1};
    std::cout << "transform " << pos << ":" << std::endl;
    std::cout << getModelMatrix(transform1) * pos << std::endl;
    std::cout << getModelMatrix(transform2) * pos << std::endl;

    std::cout << "view transform " << pos << ":" << std::endl;
    std::cout << getViewMatrix(transform1) * (getModelMatrix(transform1) * pos) << std::endl;
    std::cout << getViewMatrix(transform2) * (getModelMatrix(transform2) * pos) << std::endl;

}