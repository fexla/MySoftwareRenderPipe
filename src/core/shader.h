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

    color shade(VertexData *v1, VertexData *v2, float t) {
        return C_WHITE;
    }

};

#endif //MYSOFTWARERENDERPIPE_SHADER_H
