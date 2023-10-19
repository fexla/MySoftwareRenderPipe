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

class mix_color_shader : public frag_shader<color> {
public:
    color shade(const color *vertexBuffer[3],
                float alpha,
                float beta,
                float gamma) {
        color c = ((*vertexBuffer[0]) * alpha + (*vertexBuffer[1]) * beta + (*vertexBuffer[2]) * gamma);
        return c;
    }
};

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
    mix_color_shader shader;
    const color *vertexBuffer[3] = {
            new color{C_RED},
            new color{C_GREEN},
            new color{C_BLUE},
    };
    Vector3f pos[] = {
            Vector3f{-200, -200},
            Vector3f{200, -200},
            Vector3f{0, 200},
    };
    for (auto &v: pos) {
//        v /= 2;
        v += Vector3f{W / 2, H / 2};
    }
    rasterize_triangle(a, vertexBuffer, pos, shader);
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