//
// Created by q on 2023/10/20.
//

#ifndef MYSOFTWARERENDERPIPE_RENDERER_H
#define MYSOFTWARERENDERPIPE_RENDERER_H

#include "vector"

#include "model.h"
#include "transform.h"
#include "camera.h"
#include "buffer.h"
#include "rasterization.h"
#include "light.h"

struct vertex_wpos_cpos_norm_uv_dep {
    Vector4f worldPos;
    Vector4f clipPos;
    Normal norm;
    Texcoord uv;
    float dep;
};

//默认下渲染管线中的顶点数据类型
using DefVtxDataInPip = vertex_wpos_cpos_norm_uv_dep;

class material {
public:
    virtual void renderTarget(buffer2d<color> &, model &, std::vector<DefVtxDataInPip> &) const;

    mutable Matrix4x4 *obj2world;
    mutable Matrix3x3 *dir2world;
    mutable std::vector<std::unique_ptr<direction_light>> *directionLights;
protected:
    template<typename VertexData, typename Shader>
    std::enable_if_t<std::is_base_of_v<frag_shader<VertexData>, Shader>, void>
    shadeTarget(buffer2d<color> &renderBuffer,
                model &model,
                std::vector<VertexData> &vData,
                Shader &shader) const {
        for (int t = 0; t < model.triangles.size(); ++t) {
            auto &triangle = model.triangles[t];
            const DefVtxDataInPip *triangleVertexData[3]{
                    &vData[triangle[0]],
                    &vData[triangle[1]],
                    &vData[triangle[2]],
            };
            Vector3f vertexScreenPos[3];
            for (int j = 0; j < 3; ++j) {
                vertexScreenPos[j] = {
                        (vData[triangle[j]].clipPos[0] / 2 + 0.5f) * renderBuffer.getWidth(),
                        (vData[triangle[j]].clipPos[1] / 2 + 0.5f) * renderBuffer.getHeight(),
                        (vData[triangle[j]].clipPos[2]),
                };
            }
            rasterize_triangle(
                    &renderBuffer,
                    triangleVertexData,
                    vertexScreenPos,
                    shader
            );
        }
    }
};

const material DEFAULT_MATERIAL{};

struct scene_obj {
    std::string modelId;
    transform objTransform;
    const material *objMaterial;

    scene_obj(std::string modelId, const transform &objTransform) :
            modelId(std::move(modelId)), objTransform(objTransform), objMaterial(&DEFAULT_MATERIAL) {}

    scene_obj(std::string modelId, const transform &objTransform, material *objMaterial) :
            modelId(std::move(modelId)), objTransform(objTransform), objMaterial(objMaterial) {}
};

class renderer {
public:
    int render_width, render_height;

    buffer2d<color> renderBuffer;
    buffer2d<float> depthBuffer;

    std::map<std::string, model> models;
    std::vector<scene_obj> objs;
    std::vector<std::unique_ptr<direction_light>> directionLights;

    camera mainCamera;

    renderer(int renderWidth, int renderHeight);

    void render();

    void refreshBuffer();

    void addModel(const std::string &modelId, const model &&m);

    void addObj(const scene_obj &obj);

private :
    std::vector<DefVtxDataInPip> geometryProcess
            (Matrix4x4 &view_mat, Matrix4x4 &proj_mat, Matrix4x4 &model_mat, scene_obj obj);
};


#endif //MYSOFTWARERENDERPIPE_RENDERER_H
