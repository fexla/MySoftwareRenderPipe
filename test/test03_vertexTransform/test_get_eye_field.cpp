//
// Created by q on 2023/10/26.
//

#include "iostream"

#include "camera.h"
#include "renderer_math.h"


int main() {
    camera defaultCamera;
    defaultCamera.mode = ProjectionMode::Orthogonal;
    defaultCamera.size = 5;
    auto vertices = defaultCamera.getEyeFieldVertices();
    for (auto &v: vertices) {
        std::cout << v << std::endl;
    }
    std::cout << std::endl;

    defaultCamera.trans.position = {1, 2, 3};
    std::cout << "Positon: " << defaultCamera.trans.position << std::endl;
    vertices = defaultCamera.getEyeFieldVertices();
    for (auto &v: vertices) {
        std::cout << v << std::endl;
    }
    std::cout << std::endl;

    defaultCamera.trans.position = {1, 2, 3};
    defaultCamera.trans.rotation = {0, M_PI / 6, 0};
    std::cout << "Positon: " << defaultCamera.trans.position << std::endl;
    std::cout << "Rotation: "
              << defaultCamera.trans.rotation.x << ","
              << defaultCamera.trans.rotation.y << ","
              << defaultCamera.trans.rotation.z << "," << std::endl;
    vertices = defaultCamera.getEyeFieldVertices();
    for (auto &v: vertices) {
        std::cout << v << std::endl;

    }
}