//
// Created by q on 2023/10/19.
//

#ifndef MYSOFTWARERENDERPIPE_SHADER_H
#define MYSOFTWARERENDERPIPE_SHADER_H


#include "color.h"

class point_shader {
public:
    virtual ~point_shader() = default;

    virtual color shade() {
        return C_WHITE;
    }

};

template<typename VertexData>
class line_frag_shader {
public:
    virtual ~line_frag_shader() = default;

    virtual color shade(VertexData *v1, VertexData *v2, float t) {
        return C_WHITE;
    }

};

#endif //MYSOFTWARERENDERPIPE_SHADER_H
