//
// Created by q on 2023/10/20.
//
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#define STB_IMAGE_IMPLEMENTATION

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
#include "fps_counter.h"
#include "light_with_shadow.h"

using std::string;
using std::map;
using std::vector;

const int W = 600;
const int H = 600;

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

template<typename DepthBuffer>
void showdepth(DepthBuffer &zBuffer) {
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            int x = 1.0 * i * zBuffer.getWidth() / W;
            int y = 1.0 * j * zBuffer.getHeight() / H;
            buffer[(j * W + i) * 3] = (zBuffer[x][y] / 2 + 0.5) * 255;
            buffer[(j * W + i) * 3 + 1] = (zBuffer[x][y] / 2 + 0.5) * 255;
            buffer[(j * W + i) * 3 + 2] = (zBuffer[x][y] / 2 + 0.5) * 255;
        }
    }
}

vector<std::pair<string, std::pair<string, string>>> modelFiles{
        {"bunny",
                {
//                        R"(models\bunny\bunny_n.obj)",
                        R"(models\bunny\bunny_fix_n.obj)",
                        R"()"
                }
        },
//        {"crate",
//                {
//                        R"(models\Crate\Crate1.obj)",
//                        R"(models\Crate\crate_1.jpg)",
//                }
//        },
        {"cube",
                {
                        R"(models\cube\cube.obj)",
                        "",
                }
        },
        {"spot",
                {
                        R"(models\spot\spot_triangulated_good.obj)",
                        R"(models\spot\spot_texture.png)",
                }
        },
        {"rock",
                {
                        R"(models\rock\rock.obj)",
                        R"()"
                }
        },
};
vector<std::pair<string, transform>> sceneObjects{
//        {string{"bunny"}, {Vector3f{0, 0, -5}, Vector3f{50, 50, 50}, {}}},
        {string{"spot"}, {Vector3f{0, 1, -5}, Vector3f{3, 3, 3}, {}}},
        {string{"cube"},  {Vector3f{0, 1.5, 8},  Vector3f{1, 3, 1},      {0, 2, 0}}},
        {string{"cube"},  {Vector3f{3, 0, 1},  Vector3f{3, 1, 1},      {4, 4, 0}}},
        {string{"cube"},  {Vector3f{0, -1, 0}, Vector3f{10, 0.1, 10}, {}}},
};

material_lambert material;
material_texture material_t;
std::vector<std::unique_ptr<direction_light>> lights;
int x = 0;

void init(renderer &r) {
    lights.emplace_back(new direction_light_shadow{1600, Vector3f{0, -1, 0}.normalize(), 0.3});
    transform camera = {{16,   15,              0},
                        {-0.5, 3.1415926 * 0.5, 0}};
    r.mainCamera = {camera};
    r.mainCamera.mode = ProjectionMode::Orthogonal;
    r.mainCamera.size = 12;
    r.mainCamera.aspect = 1.0 * W / H;
    r.mainCamera.far = -30;

//    auto image_data = cv::imread("", cv::IMREAD_UNCHANGED);
//    r.mainCamera.mode = ProjectionMode::Perspective;
//    r.mainCamera.aspect = 1.0 * W / H;
//    r.mainCamera.far = -50;
    material.depthBuffer = &r.depthBuffer;
    material_t.depthBuffer = &r.depthBuffer;
    for ( auto& [m_name, path]: modelFiles) {
        r.addModel(m_name, model{path.first, path.second});
    }
    for (const auto& [obj_id, obj_tran]: sceneObjects) {
        scene_obj obj{obj_id, obj_tran};
        if(obj_id == "spot"){
            obj.objMaterial = &material_t;
        }else{
            obj.objMaterial = &material;
        }
        r.addObj(obj);
    }
    r.directionLights = std::move(lights);
    material_t.texture = &r.models["spot"].texture;
}


int main() {
    renderer r{W, H};
    init(r);
    GLFWwindow *window;

    /* Initialize the library */
    if(!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(W, H, "Hello World", NULL, NULL);
    if(!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    int x = 0;
    fpsCounter fpsCounter;
    while (!(glfwWindowShouldClose(window))) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        r.objs[0].objTransform.rotation.y += 0.01;
        r.render();
        refresh(r.renderBuffer);
//        showdepth(dynamic_cast<direction_light_shadow *>(r.directionLights[0].get())->zBuffer);
        fpsCounter.addFrame(std::chrono::system_clock::now());
        r.directionLights[0].get()->direction = Vector3f{cos(x * 0.1f), -1, sin(x * 0.1f)}.normalize();
        x++;
        std::cout << "====================frame====================\n";
        std::cout << "fps: " << fpsCounter.getFPS() << '\n';
        glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_BYTE, buffer);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}