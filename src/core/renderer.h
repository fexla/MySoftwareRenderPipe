//
// Created by q on 2023/10/20.
//

#ifndef MYSOFTWARERENDERPIPE_RENDERER_H
#define MYSOFTWARERENDERPIPE_RENDERER_H

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

};


#endif //MYSOFTWARERENDERPIPE_RENDERER_H
