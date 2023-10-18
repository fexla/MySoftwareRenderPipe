//
// Created by q on 2023/10/17.
//
#include "Matrix.h"
#include "iostream"


int main() {
    std::cout << "¾ØÕó³õÊ¼»¯£º" << std::endl;
    Matrix<double, 2, 4> m1;
    m1[0][0] = 1;
    m1[1][1] = 11;
    std::cout << m1 << std::endl;
    Matrix<double, 1, 5> m2(10.0);
    std::cout << m2 << std::endl;
    Matrix<double, 3, 3> m3{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << m3 << std::endl;

    std::cout << "¾ØÕó¼Ó¼õ£º" << std::endl;
    auto m4 = m3 + m3;
    std::cout << m3 << "+\n" << m3 << "=\n" << (m3 + m3) << std::endl;
    std::cout << m4 << "-\n" << m3 << "=\n" << (m4 - m3) << std::endl;
    std::cout << m3 << "+=\n" << m3 << "=>\n" << (m3 += m3) << std::endl;
    m3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << m3 << "-=\n" << m3 << "=>\n" << (m3 -= m3) << std::endl;
    m3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << "¾ØÕó³Ë·¨£º" << std::endl;
    std::cout << m3 << "*\n" << m3 << "=\n" << (m3 * m3) << std::endl;
    Matrix<double, 1, 4> m5{2, 0, 2, 3};
    Matrix<double, 4, 1> m6{1, 0, 1, 7};
    std::cout << m5 << "*\n" << m6 << "=\n" << (m5 * m6) << std::endl;

    std::cout << "¾ØÕó³ËÊı×Ö£º" << std::endl;
    std::cout << m3 << "*3=\n" << (m3 * 3) << std::endl;
    std::cout << m3 << "*=3\t=>\n" << ((m3 *= 3), m3) << std::endl;
    m3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "3*\n" << m3 << "=\n" << (3 * m3) << std::endl;
    std::cout << m3 << "/3=\n" << (m3 / 3) << std::endl;
    std::cout << m3 << "/=3\t=>\n" << ((m3 /= 3), m3) << std::endl;
    m3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << m3 << "/3.0=\n" << (m3 / 3.0) << std::endl;
    std::cout << m3 << "/=3.0\t=>\n" << ((m3 /= 3.0), m3) << std::endl;
    m3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << "¾ØÕó×ªÖÃ£º" << std::endl;
    std::cout << m3;
    std::cout << "×ªÖÃ=>" << std::endl;
    std::cout << m3.transpose();
}