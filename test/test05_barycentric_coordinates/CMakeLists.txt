add_executable(test05_0 test_barycentric_coordinates.cpp)

target_include_directories(test05_0 PUBLIC
        ${EXTERNAL}/glfw/include
)

target_link_libraries(test05_0 PUBLIC
        OpenGL32
        ${EXTERNAL}/glfw/lib-mingw-w64/glfw3.dll
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3.a
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3dll.a
        renderer_math
        renderer_core
)

add_executable(test05_1 test_barycentric_coordinates2.cpp)

target_include_directories(test05_1 PUBLIC
        ${EXTERNAL}/glfw/include
)

target_link_libraries(test05_1 PUBLIC
        OpenGL32
        ${EXTERNAL}/glfw/lib-mingw-w64/glfw3.dll
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3.a
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3dll.a
        renderer_math
        renderer_core
)

