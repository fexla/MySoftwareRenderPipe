//
// Created by q on 2023/10/18.
//

#ifndef MYSOFTWARERENDERPIPE_RASTERIZATION_H
#define MYSOFTWARERENDERPIPE_RASTERIZATION_H

#include "renderer_math.h"
#include "shader.h"

template<typename GraphicsBuffer, typename Shader=point_shader>
inline std::enable_if_t<std::is_base_of_v<point_shader, Shader>, void>
rasterize_point(GraphicsBuffer *buffer,
                Vector2i pos,
                Shader &shader) {
    (*buffer)[pos[0]][pos[1]] = shader.shade();
}
#endif //MYSOFTWARERENDERPIPE_RASTERIZATION_H
