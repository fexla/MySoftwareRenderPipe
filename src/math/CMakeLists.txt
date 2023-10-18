add_library(renderer_math STATIC
        Matrix.h
        Vector.h
        Rotation.h)

set_target_properties(renderer_math PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(renderer_math PUBLIC cxx_std_17)
target_include_directories(renderer_math PUBLIC ./)