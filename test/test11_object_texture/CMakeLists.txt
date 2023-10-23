add_executable(test11_0 test_object_texture.cpp)

target_include_directories(test11_0 PUBLIC
        ${EXTERNAL}/glfw/include
)

target_link_libraries(test11_0 PUBLIC
        OpenGL32
        ${EXTERNAL}/glfw/lib-mingw-w64/glfw3.dll
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3.a
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3dll.a
        renderer_math
        renderer_core
)

