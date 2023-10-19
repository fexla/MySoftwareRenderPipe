//
// Created by q on 2023/10/19.
//
#include <random>
#include "renderer_math.h"
#include "utility.h"

using std::cout;
using std::endl;

void test_triangle(array<Vector2f, 3> &triangle) {
    cout << "test triangle:\n";
    for (int i = 0; i < 3; ++i) {
        cout << triangle[i] << '\n';
    }
    cout << "result: " << isTriangleClockwise(triangle) << '\n';
}

int main() {
    array<Vector2f, 3> triangle1{
            Vector2f{0, 0},
            Vector2f{3, 0},
            Vector2f{0, 4},
    };
    test_triangle(triangle1);
    array<Vector2f, 3> triangle2{
            Vector2f{3, 0},
            Vector2f{0, 0},
            Vector2f{0, 4},
    };
    test_triangle(triangle2);
    std::mt19937_64 rngl;
    for (int i = 0; i < 10; ++i) {
        array<Vector2f, 3> triangle{
                Vector2f{(float) (rngl() % 10), (float) (rngl() % 10)},
                Vector2f{(float) (rngl() % 10), (float) (rngl() % 10)},
                Vector2f{(float) (rngl() % 10), (float) (rngl() % 10)},
        };
        test_triangle(triangle);
    }

};