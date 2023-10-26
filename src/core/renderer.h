//
// Created by q on 2023/10/20.
//

#ifndef MYSOFTWARERENDERPIPE_RENDERER_H
#define MYSOFTWARERENDERPIPE_RENDERER_H

#include "vector"
#include "bitset"

#include "buffer.h"
#include "camera.h"
#include "color.h"
#include "materials/material.h"
#include "model.h"
#include "scene_obj.h"


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

    void updateShadowMap();
};


#endif //MYSOFTWARERENDERPIPE_RENDERER_H
