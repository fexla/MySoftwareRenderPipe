//
// Created by q on 2023/10/20.
//

#include <limits>

#include "renderer.h"

void renderer::render() {
    refreshBuffer();
    auto view_mat = mainCamera.getViewMatrix();
    auto proj_mat = mainCamera.getProjectionMatrix();
    for (int i = 0; i < objs.size(); ++i) {
        auto &obj = objs[i];
        auto &model = models[obj.modelId];
        auto model_mat = getModelMatrix(obj.objTransform);
        std::vector<DefVtxDataInPip> vData{model.vertices.size()};

        //准备顶点
        for (int v = 0; v < model.vertices.size(); ++v) {
            auto modelData = model.vertices[v];
            Vector4f pos = {modelData.pos[0], modelData.pos[1], modelData.pos[2], 1};
            pos[3] = 1;
            auto worldPos = model_mat * pos;
            auto viewPos = view_mat * worldPos;
            auto clipPos = proj_mat * viewPos;
            clipPos /= clipPos[3];
            vData[v] = DefVtxDataInPip{
                    worldPos,
                    clipPos,
                    modelData.norm,
                    modelData.texcoord,
                    -viewPos[2]};
        }
        auto dir2world = obj.objTransform.rotation.rotationMatrix3x3();
        //光栅化
        obj.objMaterial->obj2world = &model_mat;
        obj.objMaterial->dir2world = &dir2world;
        obj.objMaterial->directionLights = &directionLights;
        obj.objMaterial->renderTarget(renderBuffer, model, vData);
    }
}

void renderer::addModel(const std::string &modelId, const model &&m) {
    models.insert({modelId, m});
}

renderer::renderer(int renderWidth, int renderHeight) :
        render_width(renderWidth),
        render_height(renderHeight),
        renderBuffer(renderWidth, renderHeight),
        depthBuffer(renderWidth, renderHeight) {}

void renderer::addObj(const scene_obj &obj) {
    objs.push_back(obj);
}

void renderer::refreshBuffer() {
    for (int i = 0; i < render_width; ++i) {
        for (int j = 0; j < render_height; ++j) {
            renderBuffer[i][j] = C_BLACK;
            depthBuffer[i][j] = std::numeric_limits<float>::max();
        }
    }
}

void material::renderTarget(buffer2d<color> &renderBuffer, model &model, std::vector<DefVtxDataInPip> &vData) const {
    //光栅化
    frag_shader<DefVtxDataInPip> shader;
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
