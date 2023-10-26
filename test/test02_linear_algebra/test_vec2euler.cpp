//
// Created by q on 2023/10/25.
//

#include "iostream"

#include "rotation.h"

void outputEuler(const EulerAngle &rotation) {
    using std::cout;
    using std::endl;
    cout << "rotation: "
         << rotation.x / M_PI * 180 << " - "
         << rotation.y / M_PI * 180 << " - "
         << rotation.z / M_PI * 180 << endl;
    auto mat = (Vector4f) (rotation.rotationMatrix() * Vector4f{1, 0, 0, 0});
    cout << "check: " << mat << endl << endl;
}

int main() {
    using std::cout;
    using std::endl;
    Vector3f v1 = {1, 0, 0};
    Vector3f v2 = {0, 1, 0};
    Vector3f v3 = {0, 0, 1};
    Vector3f v4 = {2, 0, 1};
    Vector3f v5 = {2, 3, 5};
    Vector3f v6 = {-1, 1, 0};
    Vector3f v7 = {0, -1, -1};
    cout << "vector: " << v1 << endl;
    outputEuler(vec2Euler(v1));
    cout << "vector: " << v2 << endl;
    outputEuler(vec2Euler(v2));
    cout << "vector: " << v3 << endl;
    outputEuler(vec2Euler(v3));
    cout << "vector: " << v4 << endl;
    outputEuler(vec2Euler(v4));
    cout << "vector: " << v5 << endl;
    outputEuler(vec2Euler(v5));
    cout << "vector: " << v6 << endl;
    outputEuler(vec2Euler(v6));
    cout << "vector: " << v7 << endl;
    outputEuler(vec2Euler(v7));
}