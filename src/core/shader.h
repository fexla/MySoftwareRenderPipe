//
// Created by q on 2023/10/19.
//

#ifndef MYSOFTWARERENDERPIPE_SHADER_H
#define MYSOFTWARERENDERPIPE_SHADER_H


#include "color.h"

class point_shader {
public:
    ~point_shader() = default;

    color shade() {
        return C_WHITE;
    }

};

template<typename VertexData>
class line_frag_shader {
public:
    ~line_frag_shader() = default;

    color shade(const VertexData *v1, const VertexData *v2, float t) {
        return C_WHITE;
    }

};

template<typename VertexData>
class frag_shader {
public:
    ~frag_shader() = default;

    color shade(const VertexData *vertexBuffer[3],
                float alpha,
                float beta,
                float gamma) {
        return C_WHITE;
    }

};

#endif //MYSOFTWARERENDERPIPE_SHADER_H
