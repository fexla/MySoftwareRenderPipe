add_executable(test15_0 test_triangle_culling.cpp)

target_include_directories(test15_0 PUBLIC
        ${EXTERNAL}/glfw/include
)

target_link_libraries(test15_0 PUBLIC
        OpenGL32
        ${EXTERNAL}/glfw/lib-mingw-w64/glfw3.dll
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3.a
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3dll.a
        renderer_math
        renderer_core
)

