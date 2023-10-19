//
// Created by q on 2023/10/19.
//
#include "GLFW/glfw3.h"
#include "renderer_math.h"
#include "color.h"
#include "rasterization.h"

const int W = 640;
const int H = 480;

char buffer[W * H * 3];

template<typename Graphic_Buffer>
void refresh(Graphic_Buffer *graphicBuffer) {
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            buffer[(j * W + i) * 3] = (*graphicBuffer)[i][j][0] * 255;
            buffer[(j * W + i) * 3 + 1] = (*graphicBuffer)[i][j][1] * 255;
            buffer[(j * W + i) * 3 + 2] = (*graphicBuffer)[i][j][2] * 255;
        }
    }
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

    auto a = new matrix<color, W, H>;
    point_shader shader;
    for (int i = -90; i < 91; i += 4) {
        rasterize_point(a, {W / 2 + i, H / 2}, shader);
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        refresh(a);

        glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_BYTE, buffer);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}