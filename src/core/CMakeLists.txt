add_library(renderer_core STATIC
        transform.h
        transform.cpp
        rasterization.h
        shader.h
        color.h
)

set_target_properties(renderer_core PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(renderer_core PUBLIC cxx_std_17)
target_include_directories(renderer_core PUBLIC ./)
target_link_libraries(renderer_core PUBLIC renderer_math)