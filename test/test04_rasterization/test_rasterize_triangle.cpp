//
// Created by q on 2023/10/19.
//
#include <random>
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
    frag_shader<color> shader;
    const color *vertexBuffer[3];
    int cellSize = 200;
    std::mt19937_64 rngl;
    for (int c_x = 0; c_x < W / cellSize; ++c_x) {
        for (int c_y = 0; c_y < H / cellSize; ++c_y) {
            Vector2i vertexPos[3]{
                    Vector2i{(int) (rngl() % cellSize), (int) (rngl() % cellSize)},
                    Vector2i{(int) (rngl() % cellSize), (int) (rngl() % cellSize)},
                    Vector2i{(int) (rngl() % cellSize), (int) (rngl() % cellSize)}
            };
            std::cout << "draw " << vertexPos[0] << '\t' << vertexPos[1] << '\t' << vertexPos[2] << '\n';
            for (int i = 0; i < 3; ++i) {
                vertexPos[i] += {c_x * cellSize, c_y * cellSize};
            }
            rasterize_triangle(a, vertexBuffer, vertexPos, shader);
        }
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