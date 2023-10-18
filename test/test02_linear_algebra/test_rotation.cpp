//
// Created by q on 2023/10/18.
//
#include "rotation.h"
#include "iostream"


int main() {
    Vector4f pos1{1, 0, 0, 1};
    std::cout << "��" << pos1 << "��x����ת45��:" << std::endl;
    std::cout << EulerAngle{45.0 / 180 * 3.1415926, 0, 0}.rotationMatrix() * pos1;
    std::cout << "��" << pos1 << "��y����ת45��:" << std::endl;
    std::cout << EulerAngle{0,45.0 / 180 * 3.1415926,  0}.rotationMatrix() * pos1.asMatrix();
    std::cout << "��" << pos1 << "��z����ת45��:" << std::endl;
    std::cout << EulerAngle{ 0, 0,45.0 / 180 * 3.1415926}.rotationMatrix() * pos1.asMatrix();
}