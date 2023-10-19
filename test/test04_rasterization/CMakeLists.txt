add_executable(test04_0 test_rasterize_point.cpp)

target_include_directories(test04_0 PUBLIC
        ${EXTERNAL}/glfw/include
)

target_link_libraries(test04_0 PUBLIC
        OpenGL32
        ${EXTERNAL}/glfw/lib-mingw-w64/glfw3.dll
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3.a
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3dll.a
        renderer_math
        renderer_core
)

add_executable(test04_1 test_rasterize_line.cpp)

target_include_directories(test04_1 PUBLIC
        ${EXTERNAL}/glfw/include
)

target_link_libraries(test04_1 PUBLIC
        OpenGL32
        ${EXTERNAL}/glfw/lib-mingw-w64/glfw3.dll
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3.a
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3dll.a
        renderer_math
        renderer_core
)

