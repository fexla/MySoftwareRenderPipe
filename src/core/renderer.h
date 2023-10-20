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

struct scene_obj {
    std::string modelId;
    transform transform;
};

struct vertex_wpos_cpos_norm_uv_dep {
    Vector4f worldPos;
    Vector4f clipPos;
    Normal norm;
    Texcoord uv;
    float dep;
};

//默认下渲染管线中的顶点数据类型
using DefVtxDataInPip = vertex_wpos_cpos_norm_uv_dep;

class renderer {
public:
    int render_width, render_height;

    buffer2d<color> renderBuffer;

    camera mainCamera;

    renderer(int renderWidth, int renderHeight);

    void render();

    void addModel(const std::string &modelId, const model &&m);

    void addObj(const scene_obj &obj);

    std::map<std::string, model> models;
    std::vector<scene_obj> objs;
};


#endif //MYSOFTWARERENDERPIPE_RENDERER_H
