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

class shader_lerp_color : public line_frag_shader<color> {
public:
    color shade(const color *v1, const color *v2, float t) {
        return {
                v1->r * (1 - t) + v2->r * t,
                v1->g * (1 - t) + v2->g * t,
                v1->b * (1 - t) + v2->b * t,
                v1->a * (1 - t) + v2->a * t,
        };
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
    line_frag_shader<color> shader;
    shader_lerp_color shader_lerp;

    rasterize_line(a, {W / 2 - 40 - 100, H / 2 + 100}, {W / 2 + 40 - 100, H / 2 + 100},
                   &C_WHITE, &C_BLACK, shader);
    rasterize_line(a, {W / 2 - 100, H / 2 - 40 + 100}, {W / 2 - 100, H / 2 + 40 + 100},
                   &C_WHITE, &C_BLACK, shader);
    rasterize_line(a, {W / 2 - 40 - 100, H / 2 - 40}, {W / 2 + 40 - 100, H / 2 + 40},
                   &C_WHITE, &C_BLACK, shader);
    rasterize_line(a, {W / 2 - 40 - 100, H / 2 + 40}, {W / 2 + 40 - 100, H / 2 - 40},
                   &C_WHITE, &C_BLACK, shader);
    rasterize_line(a, {W / 2 - 40 - 100, H / 2 - 60 - 100}, {W / 2 + 40 - 100, H / 2 + 60 - 100},
                   &C_WHITE, &C_BLACK, shader);
    rasterize_line(a, {W / 2 - 40 - 100, H / 2 + 60 - 100}, {W / 2 + 40 - 100, H / 2 - 60 - 100},
                   &C_WHITE, &C_BLACK, shader);

    int pointNum = 50;
    float lineLen = 80;
    for (int i = 0; i < pointNum; ++i) {
        float angle = 1.0 * i / pointNum * M_PI * 2;
        Vector3f pos{(W / 2 + 100 + lineLen * cos(angle)),
                     (H / 2 + lineLen * sin(angle))};
        rasterize_line(a, {W / 2 + 100, H / 2}, pos, &C_RED, &C_Blue, shader_lerp);
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