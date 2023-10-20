add_executable(test09_0 test_simple_scene.cpp)

target_include_directories(test09_0 PUBLIC
        ${EXTERNAL}/glfw/include
)

target_link_libraries(test09_0 PUBLIC
        OpenGL32
        ${EXTERNAL}/glfw/lib-mingw-w64/glfw3.dll
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3.a
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3dll.a
        renderer_math
        renderer_core
)

