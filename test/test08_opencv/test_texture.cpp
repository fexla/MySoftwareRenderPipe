//
// Created by q on 2023/10/20.
//
#include "GLFW/glfw3.h"
#include "texture.h"

const std::string filepath = "lappland.png";

const int W = 1024;
const int H = 1024;

char buffer[W * H * 3];

void set_pixel(char *buffer, size_t x, size_t y, char r, char g, char b) {
    buffer[y * W * 3 + x * 3] = r;
    buffer[y * W * 3 + x * 3 + 1] = g;
    buffer[y * W * 3 + x * 3 + 2] = b;

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

    Texture texture;
    texture.loadFromFile(filepath);

    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            auto px_color = texture.getColor(1.0 * i / W, 1.0 * j / H);
            px_color *= px_color.a;
            set_pixel(buffer, i, j, px_color.r * 255, px_color.g * 255, px_color.b * 255);

        }
    }
    std::cout << "ok" << std::endl;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_BYTE, buffer);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}