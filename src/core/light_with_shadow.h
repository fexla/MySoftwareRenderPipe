//
// Created by q on 2023/10/26.
//

#ifndef MYSOFTWARERENDERPIPE_LIGHT_WITH_SHADOW_H
#define MYSOFTWARERENDERPIPE_LIGHT_WITH_SHADOW_H

#include "vector"

#include "camera.h"
#include "light.h"
#include "model.h"
#include "renderer_math.h"
#include "scene_obj.h"

struct vertex_cpos {
    Vector4f clipPos;
};

using ShadowVertexData = vertex_cpos;

class light_with_shadow {

public:
    light_with_shadow(int bufferSize) : zBuffer(bufferSize, bufferSize) {}

    /**
     * 得到特定坐标（世界坐标系）的阴影值
     * @return
     */
    virtual float getShadow(Vector4f) = 0;

    /**
     * 根据场景中的物体更新深度缓冲
     */
    virtual void updateShadow(std::map<std::string, model> &, std::vector<scene_obj> &) = 0;

    /**
     * 更新Frustrum，将参数中的点（世界坐标系）都包围在内
     */
    virtual void updateFrustrum(const std::vector<Vector4f> &) = 0;

    //深度缓冲
    buffer2d<float> zBuffer;
protected:
    //世界坐标的点转换到深度图坐标的转换矩阵
    Matrix4x4 vpMat;
};

class direction_light_shadow : public light_with_shadow, public direction_light {
public:
    direction_light_shadow(int bufferSize, const Vector3f &direction, float intensity);

private:
    /**
     * 得到特定坐标（世界坐标系）的阴影值
     * @return
     */
    float getShadow(Vector4f) override;

    /**
     * 根据场景中的物体更新深度缓冲
     */
    void updateShadow(std::map<std::string, model> &, std::vector<scene_obj> &) override;

    /**
     * 更新Frustrum，将参数中的点（世界坐标系）都包围在内
     */
    void updateFrustrum(const std::vector<Vector4f> &) override;

};

#endif //MYSOFTWARERENDERPIPE_LIGHT_WITH_SHADOW_H
