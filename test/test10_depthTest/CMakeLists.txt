add_executable(test10_0 test_depthtest.cpp)

target_include_directories(test10_0 PUBLIC
        ${EXTERNAL}/glfw/include
)

target_link_libraries(test10_0 PUBLIC
        OpenGL32
        ${EXTERNAL}/glfw/lib-mingw-w64/glfw3.dll
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3.a
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3dll.a
        renderer_math
        renderer_core
)

