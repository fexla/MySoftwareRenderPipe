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
    std::cout << transform1.getModelMatrix() * pos << std::endl;
    std::cout << transform2.getModelMatrix() * pos << std::endl;
}