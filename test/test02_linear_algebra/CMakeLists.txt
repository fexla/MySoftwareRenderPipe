add_executable(test02_0 test_matrix.cpp)
target_link_libraries(test02_0 renderer_math)

add_executable(test02_1 test_vector.cpp)
target_link_libraries(test02_1 renderer_math)

add_executable(test02_2 test_rotation.cpp)
target_link_libraries(test02_2 renderer_math)

add_executable(test02_3 test_vec2euler.cpp)
target_link_libraries(test02_3 renderer_math)