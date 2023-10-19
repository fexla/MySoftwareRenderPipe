add_library(renderer_math STATIC
        matrix.h
        mvector.h
        renderer_math.h
        rotation.h
        barycentric_coordinates.h
        rm_type_names.h)

set_target_properties(renderer_math PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(renderer_math PUBLIC cxx_std_17)
target_include_directories(renderer_math PUBLIC ./)