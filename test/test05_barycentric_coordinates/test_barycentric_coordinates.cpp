//
// Created by q on 2023/10/19.
//
#include "renderer_math.h"
#include "iostream"

using std::cout;
using std::endl;

int main() {
    array<Vector2f, 3> pos{
            Vector2f{0, 0},
            Vector2f{3, 0},
            Vector2f{0, 4},
    };
    cout << "triangle:\n";
    cout << pos[0] << endl;
    cout << pos[1] << endl;
    cout << pos[2] << endl;
    {
        auto p = Vector2f{0, 0};
        auto [alpha, beta, gamma] = barycentric_coordinates2d(p, pos);
        cout << "coordinate of " << p << " : " << alpha << " " << beta << " " << gamma << endl;
    }
    {
        auto p = Vector2f{1, 0};
        auto [alpha, beta, gamma] = barycentric_coordinates2d(p, pos);
        cout << "coordinate of " << p << " : " << alpha << " " << beta << " " << gamma << endl;
    }
    {
        auto p = Vector2f{1, 1};
        auto [alpha, beta, gamma] = barycentric_coordinates2d(p, pos);
        cout << "coordinate of " << p << " : " << alpha << " " << beta << " " << gamma << endl;
    }
}