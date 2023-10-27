add_library(renderer_core STATIC
        buffer.h
        camera.h
        color.h
        fps_counter.cpp
        fps_counter.h
        light.h
        light_with_shadow.cpp
        light_with_shadow.h
        materials/material_lambert.cpp
        materials/material_lambert.h
        materials/material_texture.cpp
        materials/material_texture.h
        materials/material_with_depth.cpp
        materials/material_with_depth.h
        materials/material.h
        model.h
        rasterization.h
        renderer.cpp
        renderer.h
        scene_obj.h
        shader.h
        texture.h
        transform.cpp
        transform.h
)

set_target_properties(renderer_core PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(renderer_core PUBLIC cxx_std_17)
target_include_directories(renderer_core PUBLIC
        ./
        ${EXTERNAL}/obj_loader
)
target_link_libraries(renderer_core PUBLIC
        renderer_math
        ${OpenCV_LIBS}
)