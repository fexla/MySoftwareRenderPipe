//
// Created by q on 2023/10/26.
//
#include "cmath"

#include "light_with_shadow.h"
#include "rasterization.h"

float direction_light_shadow::getShadow(Vector4f pos) {
    Vector4f clipPos = vpMat * pos;
    if (clipPos[0] > 1 || clipPos[0] < -1 ||
        clipPos[1] > 1 || clipPos[1] < -1 ||
        clipPos[2] > 1 || clipPos[2] < -1) {
        return 1;
    }
    Vector2f bufferPos = {
            (clipPos[0] / 2 + 0.5f) * zBuffer.getWidth(),
            (clipPos[1] / 2 + 0.5f) * zBuffer.getHeight(),
    };
    float depth = clipPos[2];
//    return zBuffer[lround(bufferPos[0] + 0.5f)][lround(bufferPos[1] + 0.5f)] < depth - 0.00001;
    return zBuffer[static_cast<int>(bufferPos[0])][static_cast<int>(bufferPos[1])] < depth - 0.01;
}

static int x = 0;

//aabb确定平行光的摄像机范围
void direction_light_shadow::updateFrustrum(const std::vector<Vector4f> &points) {
    auto angle = vec2Euler(direction);
    transform viewPoint{Vector3f{0, 0, 0}, angle};
    auto view_mat = EulerAngle{0, -M_PI / 2, 0}.rotationMatrix() * getViewMatrix(viewPoint);
    Vector3f aabb[2] = {
            {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), -10},
            {std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), 10}
    };
    for (auto point: points) {
        Vector4f wPos = Vector4f{point[0], point[1], point[2], 1};
        Vector4f vPos = view_mat * wPos;

        for (int j = 0; j < 3; ++j) {
            aabb[0][j] = std::min(vPos[j]-10, aabb[0][j]);
            aabb[1][j] = std::max(vPos[j]+10, aabb[1][j]);
        }
    }
    Matrix4x4 translation_mat = getTranslationMatrix({0, 0, 0}, {
            (aabb[0][0] + aabb[1][0]) / 2,
            (aabb[0][1] + aabb[1][1]) / 2,
            (aabb[0][2] + aabb[1][2]) / 2
    });
    Matrix4x4 scale_mat = getScaleMatrix({
                                                 2.f / (aabb[1][0] - aabb[0][0]),
                                                 2.f / (aabb[1][1] - aabb[0][1]),
                                                 2.f / (aabb[1][2] - aabb[0][2]),
                                         });
    vpMat = scale_mat * translation_mat * view_mat;
}

void direction_light_shadow::updateShadow(std::map<std::string, model> &models, std::vector<scene_obj> &objs) {
    for (int i = 0; i < zBuffer.getHeight(); ++i) {
        for (int j = 0; j < zBuffer.getWidth(); ++j) {
            zBuffer[i][j] = 1;
        }
    }
    for (auto &obj: objs) {
        auto &model = models[obj.modelId];
        auto model_mat = getModelMatrix(obj.objTransform);
        auto mvp_map = vpMat * model_mat;

        std::vector<ShadowVertexData> vData{model.vertices.size()};

        //准备顶点
        for (int v = 0; v < model.vertices.size(); ++v) {
            auto modelData = model.vertices[v];
            Vector4f pos = {modelData.pos[0], modelData.pos[1], modelData.pos[2], 1};
            auto clipPos = mvp_map * pos;
            clipPos /= clipPos[3];
            vData[v] = ShadowVertexData{clipPos};
        }
        for (auto &triangle: model.triangles) {
            const ShadowVertexData *triangleVertexData[3]{
                    &vData[triangle[0]],
                    &vData[triangle[1]],
                    &vData[triangle[2]],
            };
            std::bitset<6> pointOutOfBound[3];
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    pointOutOfBound[i][j * 2] = triangleVertexData[i]->clipPos[j] > 1;
                    pointOutOfBound[i][j * 2 + 1] = triangleVertexData[i]->clipPos[j] < -1;
                }
            }
            if ((pointOutOfBound[0] & pointOutOfBound[1] & pointOutOfBound[2]).any()) {
                continue;
            }
            //正面剔除
            if (isTriangleClockwise(
                    {
                            Vector2f{triangleVertexData[0]->clipPos[0], triangleVertexData[0]->clipPos[1]},
                            Vector2f{triangleVertexData[1]->clipPos[0], triangleVertexData[1]->clipPos[1]},
                            Vector2f{triangleVertexData[2]->clipPos[0], triangleVertexData[2]->clipPos[1]},
                    })) {
                continue;
            }
            std::array<Vector3f, 3> vertexScreenPos;
            for (int j = 0; j < 3; ++j) {
                vertexScreenPos[j] = {
                        (vData[triangle[j]].clipPos[0] / 2 + 0.5f) * zBuffer.getWidth(),
                        (vData[triangle[j]].clipPos[1] / 2 + 0.5f) * zBuffer.getHeight(),
                        (vData[triangle[j]].clipPos[2]),
                };
            }
            frag_shader tmp = frag_shader<ShadowVertexData>();
            tmp.projectionMode = ProjectionMode::Orthogonal;
            rasterize_triangle<void>(
                    nullptr,
                    &zBuffer,
                    triangleVertexData,
                    vertexScreenPos,
                    tmp
            );
        }
    }
}

direction_light_shadow::direction_light_shadow(int
                                               bufferSize,
                                               const Vector3f &direction,
                                               float intensity)
        : direction_light(direction, intensity), light_with_shadow(bufferSize) {}
