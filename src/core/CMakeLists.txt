add_library(renderer_core STATIC
        transform.h
        transform.cpp
        rasterization.h
        shader.h
        color.h
        texture.h
        renderer.cpp
        renderer.h
        model.h
        camera.h
        buffer.h
        materials/material_with_depth.cpp
        materials/material_with_depth.h
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