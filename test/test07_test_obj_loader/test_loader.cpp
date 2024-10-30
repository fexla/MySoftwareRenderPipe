//
// Created by q on 2023/10/19.
//
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc

#include <iostream>
#include "tiny_obj_loader.h"

int main() {
    std::string inputfile = "models/spot/spot_triangulated_good.obj";
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

    if (!err.empty()) { // `err` may contain warning message.
        std::cerr << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }
    std::cout << "shapes.size: " << shapes.size() << std::endl;
    std::cout << "attrib.vertices.size(): " << attrib.vertices.size() << std::endl;
// Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
// Loop over faces(polygon)
        size_t index_offset = 0;
        std::cout << "shapes[s].mesh.num_face_vertices.size(): " << shapes[s].mesh.num_face_vertices.size() << std::endl;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

// Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
// access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                float vx = attrib.vertices[3 * idx.vertex_index + 0];
                float vy = attrib.vertices[3 * idx.vertex_index + 1];
                float vz = attrib.vertices[3 * idx.vertex_index + 2];
                float nx = attrib.normals[3 * idx.normal_index + 0];
                float ny = attrib.normals[3 * idx.normal_index + 1];
                float nz = attrib.normals[3 * idx.normal_index + 2];
                float tx = attrib.texcoords[2 * idx.texcoord_index + 0];
                float ty = attrib.texcoords[2 * idx.texcoord_index + 1];
            }
            index_offset += fv;

// per-face material
            shapes[s].mesh.material_ids[f];
        }
    }
}