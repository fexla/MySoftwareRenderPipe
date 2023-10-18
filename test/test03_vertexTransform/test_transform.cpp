//
// Created by q on 2023/10/18.
//
#include "GLFW/glfw3.h"
#include "transform.h"

const size_t W = 640;
const size_t H = 480;

char buffer[W * H * 3];

Vector3f points[] = {
        {1,    1,  1},
        {0.2,  1,  1},
        {0.4,  1,  1},
        {0.6,  1,  1},
        {0.8,  1,  1},
        {0,    1,  1},
        {-0.2, 1,  1},
        {-0.4, 1,  1},
        {-0.6, 1,  1},
        {-0.8, 1,  1},
        {-1,   1,  1},
        {1,    -1, 1},
        {1,    1,  -1},
        {-1,   -1, 1},
        {-1,   1,  -1},
        {1,    -1, -1},
        {-1,   -1, -1},
};

transform objectTransform = {{0, 0, 0},
                             {0, 0, 0}};
transform cameraTransform = {{16,    6,             5},
                             {-0.2,  3.1415926*0.5, 0}};

void set_pixel(char *buffer, size_t x, size_t y, char r, char g, char b) {
    if (x >= W || y >= H)return;
    buffer[y * W * 3 + x * 3] = r;
    buffer[y * W * 3 + x * 3 + 1] = g;
    buffer[y * W * 3 + x * 3 + 2] = b;
}

void set_pixels(char *buffer, size_t x, size_t y, char r, char g, char b, int size = 2) {
    for (int i = -size + 1 + x; i <= x + size - 1; ++i) {
        for (int j = -size + 1 + y; j <= y + size - 1; ++j) {
            set_pixel(buffer, i, j, r, g, b);
        }
    }
}

void set_pixels(char *buffer, Vector4f pos, char r, char g, char b, int size = 2) {
    if (pos[2] < 0)return;
    set_pixels(buffer, pos[0], pos[1], r, g, b, size);
}

int cnt = 0;

Vector4f tran(Matrix4x4 &mvp, Vector4f p) {
    p = mvp * p;
    p /= p[3];
    p = (p + Vector4f{1, 1, 1, 1}) / 2;
    p[0] *= W;
    p[1] *= H;
    return p;
}

void render(char *buffer) {
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            set_pixel(buffer, i, j, 255, 255, 255);
        }
    }
    auto mvp =
            getPerspectiveProjectionMatrix(45.0 / 180 * 3.1415926, 1.0 * W / H, 0.01, 100) *
            getViewMatrix(cameraTransform) *
            getModelMatrix(objectTransform);
    for (auto p: points) {
        Vector4f homogeneous{p[0], p[1], p[2], 1};
        homogeneous = tran(mvp, homogeneous);
        set_pixels(buffer, homogeneous, 255, 0, 0);
    }
    Vector4f origin{0, 0, 0, 1}, axis_x = {1, 0, 0, 1}, axis_y = {0, 1, 0, 1}, axis_z = {0, 0, 1, 1};
    auto mvp2 =
            getPerspectiveProjectionMatrix(45.0 / 180 * 3.1415926, 1.0 * W / H, 0.01, 100) *
            getViewMatrix(cameraTransform) *
            getModelMatrix(transform{{0, 0, 0},
                                     {}});
    origin = tran(mvp2, origin);
    axis_x = tran(mvp2, axis_x);
    axis_y = tran(mvp2, axis_y);
    axis_z = tran(mvp2, axis_z);
    set_pixels(buffer, origin, 0, 0, 0, 5);
    set_pixels(buffer, axis_x, 255, 0, 0, 5);
    set_pixels(buffer, axis_y, 0, 255, 0, 5);
    set_pixels(buffer, axis_z, 0, 0, 255, 5);
}

int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(W, H, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        cnt++;
        cnt %= 40000;
        objectTransform.rotation.y = 0.003 * cnt;
        render(buffer);
        glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_BYTE, buffer);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}