//
// Created by q on 2023/10/20.
//
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc

#include <random>
#include "map"
#include "string"
#include "vector"
#include "renderer_math.h"
#include "transform.h"
#include "texture.h"
#include "GLFW/glfw3.h"
#include "shader.h"
#include "renderer.h"
#include "materials/material_with_depth.h"
#include "materials/material_texture.h"
#include "materials/material_lambert.h"

using std::string;
using std::map;
using std::vector;

const int W = 960;
const int H = 540;

char buffer[W * H * 3];

template<typename Graphic_Buffer>
void refresh(Graphic_Buffer &graphicBuffer) {
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            buffer[(j * W + i) * 3] = graphicBuffer[i][j][0] * 255;
            buffer[(j * W + i) * 3 + 1] = graphicBuffer[i][j][1] * 255;
            buffer[(j * W + i) * 3 + 2] = graphicBuffer[i][j][2] * 255;
        }
    }
}

vector<std::pair<string, std::pair<string, string>>> modelFiles{
        {"bunny",
                {
                        R"(E:\Projects\Exercise1_SoftwareRenderPipe\models\bunny\bunny_n.obj)",
                        R"()"
                }
        },
        {"crate",
                {
                        R"(E:\Projects\Exercise1_SoftwareRenderPipe\models\Crate\Crate1.obj)",
                        R"(E:\Projects\Exercise1_SoftwareRenderPipe\models\Crate\crate_1.jpg)",
                }
        },
        {"spot",
                {
                        R"(E:\Projects\Exercise1_SoftwareRenderPipe\models\spot\spot_triangulated_good.obj)",
                        R"(E:\Projects\Exercise1_SoftwareRenderPipe\models\spot\spot_texture.png)",
                }
        },
        {"rock",
                {
                        R"(E:\Projects\Exercise1_SoftwareRenderPipe\models\rock\rock.obj)",
                        R"()"
                }
        },
};
vector<std::pair<string, transform>> sceneObjects{
        {string{"bunny"}, {Vector3f{0, 0, 0}, Vector3f{50, 50, 50}, {}}},
};

material_lambert material;
std::vector<std::unique_ptr<direction_light>> lights;

void init(renderer &r) {
    lights.emplace_back(new direction_light{Vector3f{-1, -1, -1}.normalize(), 0.8});
    transform camera = {{16,   15,              0},
                        {-0.5, 3.1415926 * 0.5, 0}};
    r.mainCamera = {camera};
    r.mainCamera.aspect = 1.0 * W / H;
    material.depthBuffer = &r.depthBuffer;
    for (auto [m_name, path]: modelFiles) {
        r.addModel(m_name, model{path.first, path.second});
    }
    for (auto [obj_id, obj_tran]: sceneObjects) {
        r.addObj({obj_id, obj_tran, &material});
    }
//    material.directionLights = &directionLights;
    r.directionLights = std::move(lights);
}


int main(void) {
    renderer r{W, H};
    init(r);
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
    while (!(glfwWindowShouldClose(window))) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        r.objs[0].objTransform.rotation.y += 0.1;
        r.render();
        refresh(r.renderBuffer);
        std::cout << "====================frame====================\n";
        glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_BYTE, buffer);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}