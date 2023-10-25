add_executable(test14_0 test_fpsCounter.cpp)

target_include_directories(test14_0 PUBLIC
        ${EXTERNAL}/glfw/include
)

target_link_libraries(test14_0 PUBLIC
        OpenGL32
        ${EXTERNAL}/glfw/lib-mingw-w64/glfw3.dll
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3.a
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3dll.a
        renderer_math
        renderer_core
)

