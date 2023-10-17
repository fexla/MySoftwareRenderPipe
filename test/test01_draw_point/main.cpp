#include "GLFW/glfw3.h"

const size_t W = 640;
const size_t H = 480;

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

//    set the center pixel to white
//    buffer[W * H / 2 * 3 + W / 2 * 3] = 255;
//    buffer[W * H / 2 * 3 + W / 2 * 3 + 1] = 255;
//    buffer[W * H / 2 * 3 + W / 2 * 3 + 2] = 255;

    //    set the center pixel to white
    set_pixel(buffer, W / 2, H / 2, 255, 255, 255);
    //    set the center pixel to red
    set_pixel(buffer, W / 2 - 10, H / 2 + 10, 255, 0, 0);
    //    set the center pixel to green
    set_pixel(buffer, W / 2, H / 2 + 10, 0, 255, 0);
    //    set the center pixel to blue
    set_pixel(buffer, W / 2 + 10, H / 2 + 10, 0, 0, 255);



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