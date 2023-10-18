//
// Created by q on 2023/10/17.
//
#include "Vector.h"
#include "iostream"


int main() {
    std::cout << "向量初始化：" << std::endl;
    Vector<double, 4> v1;
    Vector<double, 5> v2(2);
    Vector<double, 3> v3{1, 2, 3};
    Vector<double, 3> v4{3, 2, 1};
    std::cout << v1 << std::endl;
    std::cout << v3 << std::endl;
    std::cout << v2.asMatrix() << std::endl;

    std::cout << "向量加减：" << std::endl;
    std::cout << v3 << "+" << v3 << "=" << (v3 + v3) << std::endl;
    std::cout << v4 << "-" << v3 << "=" << (v4 - v3) << std::endl;
    std::cout << v3 << "+=" << v3 << "=>" << (v3 += v3) << std::endl;
    v3 = {1, 2, 3};
    std::cout << v3 << "-=" << v3 << "=>" << (v3 -= v3) << std::endl;
    v3 = {1, 2, 3};

    std::cout << "向量乘数字：" << std::endl;
    std::cout << v3 << "*3=" << (v3 * 3) << std::endl;
    std::cout << v3 << "*=3=>" << ((v3 *= 3), v3) << std::endl;
    v3 = {1, 2, 3};
    std::cout << "3*" << v3 << "=" << (3 * v3) << std::endl;
    std::cout << v3 << "/3=" << (v3 / 3) << std::endl;
    std::cout << v3 << "/=3=>" << ((v3 /= 3), v3) << std::endl;
    v3 = {1, 2, 3};

    std::cout << "向量点乘：" << std::endl;
    std::cout << v3 << " dot " << v3 << "=" << (v3.dot(v3)) << std::endl;
    std::cout << v3 << " dot " << v4 << "=" << (dot(v3, v4)) << std::endl;
    Vector<double, 3> v5 = {-4, 8, -4};
    std::cout << v3 << " dot " << v5 << "=" << (dot(v3, v5)) << std::endl;
    std::cout << v4 << " dot " << v5 << "=" << (dot(v4, v5)) << std::endl;

    std::cout << "向量插乘：" << std::endl;
    std::cout << v3 << " cross " << v3 << "=" << (v3.cross(v3)) << std::endl;
    std::cout << v3 << " cross " << v4 << "=" << (cross(v3, v4)) << std::endl;

    std::cout << "向量的模：" << std::endl;
    std::cout << v3 << " .abs " << "=" << v3.abs() << std::endl;
    std::cout << v4 << " .abs " << "=" << v4.abs() << std::endl;
    Vector<double, 3> v6 = {0.267261, 0.534522, 0.801784};
    std::cout << v6 << " .abs " << "=" << v6.abs() << std::endl;
    std::cout << v3 << " .norm " << "=" << v3.norm_vec() << std::endl;
    std::cout << v3 << " .normalize " << "=>" << (v3.normalize()) << std::endl;
    v3 = {1, 2, 3};
//    std::cout << m5 << "*\n" << m6 << "=\n" << (m5 * m6) << std::endl;

}