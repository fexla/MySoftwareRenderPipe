//
// Created by q on 2023/10/19.
//

#ifndef MYSOFTWARERENDERPIPE_COLOR_H
#define MYSOFTWARERENDERPIPE_COLOR_H

#include "renderer_math.h"

class color {
public:

    color() = default;

    color(const color &c) = default;

    color(color &&c) = default;

    color &operator=(const color &c) = default;

    color &operator=(color &&c) = default;

    color operator+(const color &rhs) const {
        return color{r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a};
    }

    color &operator+=(const color &rhs) {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        a += rhs.a;
        return *this;
    }

    color operator-(const color &rhs) const {
        return color{r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a};
    }

    color &operator-=(const color &rhs) {
        r -= rhs.r;
        g -= rhs.g;
        b -= rhs.b;
        a -= rhs.a;
        return *this;
    }

    color operator*(const float &rhs) const {
        return color{r * rhs, g * rhs, b * rhs, a * rhs};
    }

    color &operator*=(const float &rhs) {
        r *= rhs;
        g *= rhs;
        b *= rhs;
        a *= rhs;
        return *this;
    }

    color operator/(const float &rhs) const {
        return color{r / rhs, g / rhs, b / rhs, a / rhs};
    }

    color &operator/=(const float &rhs) {
        r /= rhs;
        g /= rhs;
        b /= rhs;
        a /= rhs;
        return *this;
    }

    float &operator[](int i) {
        return *(&r + i);
    }

    const float &operator[](int i) const {
        return *(&r + i);
    }

    float r, g, b, a;
};

constexpr color C_WHITE = {1, 1, 1, 1};
constexpr color C_BLACK = {0, 0, 0, 1};
constexpr color C_RED = {1, 0, 0, 1};
constexpr color C_GREEN = {0, 1, 0, 1};
constexpr color C_BLUE = {0, 0, 1, 1};
#endif //MYSOFTWARERENDERPIPE_COLOR_H
