//
// Created by q on 2023/10/20.
//

#ifndef MYSOFTWARERENDERPIPE_MODEL_H
#define MYSOFTWARERENDERPIPE_MODEL_H


#include "vector"
#include "array"
#include "tuple"
#include "renderer_math.h"
#include "texture.h"
#include "tiny_obj_loader.h"

using Triangle = std::array<int, 3>;
using Position = Vector3f;
using Normal = Vector3f;
using Texcoord = Vector2f;

struct VertexData {
    Position pos;
    Normal norm;
    Texcoord texcoord;
};

class model {
public:
    std::vector<VertexData> vertices;
    std::vector<Triangle> triangles;
    Texture texture;

    model() = default;

    model(model &&another) noexcept = default;

    model(const model &another) = default;

    model(const std::string &modelPath, Texture &&tex) : texture(tex) {
        loadModel(modelPath);
    }

    model(const std::string &modelPath, const std::string &texPath) : texture(texPath) {
        loadModel(modelPath);
    }

    void loadModel(const std::string &modelPath) {
        if (modelPath.empty()) {
            vertices.clear();
            triangles.clear();
            return;
        }
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string err;
        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, modelPath.c_str());

        if (!err.empty()) { // `err` may contain warning message.
            std::cerr << err << std::endl;
        }

        if (!ret) {
            exit(1);
        }
        vertices.resize(attrib.vertices.size());
        triangles.resize(attrib.vertices.size());
        int triangle_id = 0;

// Loop over shapes
        for (size_t s = 0; s < shapes.size(); s++) {
// Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                int fv = shapes[s].mesh.num_face_vertices[f];

// Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++) {
// access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    float vx, vy, vz, nx = 0, ny = 0, nz = 0, tx = 0, ty = 0;
                    vx = attrib.vertices[3 * idx.vertex_index + 0];
                    vy = attrib.vertices[3 * idx.vertex_index + 1];
                    vz = attrib.vertices[3 * idx.vertex_index + 2];
                    if (idx.normal_index != -1) {
                        nx = attrib.normals[3 * idx.normal_index + 0];
                        ny = attrib.normals[3 * idx.normal_index + 1];
                        nz = attrib.normals[3 * idx.normal_index + 2];
                    }

                    if (idx.texcoord_index != -1) {
                        tx = attrib.texcoords[2 * idx.texcoord_index + 0];
                        ty = attrib.texcoords[2 * idx.texcoord_index + 1];
                    }
                    vertices[idx.vertex_index] = {
                            {vx, vy, vz},
                            {nx, ny, nz},
                            {tx, ty}};
                    triangles[triangle_id][v] = idx.vertex_index;
                }
                triangle_id++;
                index_offset += fv;
            }
        }
    }
};

#endif //MYSOFTWARERENDERPIPE_MODEL_H
