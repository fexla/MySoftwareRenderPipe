//
// Created by q on 2023/10/17.
//
#include "mvector.h"
#include "iostream"


int main() {
    std::cout << "向量初始化：" << std::endl;
    mvector<double, 4> v1;
    mvector<double, 5> v2(2);
    mvector<double, 3> v3{1, 2, 3};
    mvector<double, 3> v4{3, 2, 1};
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
    mvector<double, 3> v5 = {-4, 8, -4};
    std::cout << v3 << " dot " << v5 << "=" << (dot(v3, v5)) << std::endl;
    std::cout << v4 << " dot " << v5 << "=" << (dot(v4, v5)) << std::endl;

    std::cout << "向量叉乘：" << std::endl;
    std::cout << v3 << " cross " << v3 << "=" << (v3.cross(v3)) << std::endl;
    std::cout << v3 << " cross " << v4 << "=" << (cross(v3, v4)) << std::endl;

    std::cout << "向量的模：" << std::endl;
    std::cout << v3 << " .abs " << "=" << v3.abs() << std::endl;
    std::cout << v4 << " .abs " << "=" << v4.abs() << std::endl;
    mvector<double, 3> v6 = {0.267261, 0.534522, 0.801784};
    std::cout << v6 << " .abs " << "=" << v6.abs() << std::endl;
    std::cout << v3 << " .norm " << "=" << v3.norm_vec() << std::endl;
    std::cout << v3 << " .normalize " << "=>" << (v3.normalize()) << std::endl;
    v3 = {1, 2, 3};

    std::cout << "向量与矩阵相乘：" << std::endl;
    matrix<double, 1, 3> m1 = {1, 2, 3};
    matrix<double, 3, 3> m2 = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    std::cout << v3 << "*\n" << m1 << "=\n" << (v3 * m1) << std::endl;
    std::cout << m1 << "*\n" << v3 << "=\n" << (m1 * v3) << std::endl;
    std::cout << m2 << "*\n" << v3 << "=\n" << (m2 * v3) << std::endl;

}