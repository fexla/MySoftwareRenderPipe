add_executable(test03_0 main.cpp)
target_link_libraries(test03_0 renderer_math renderer_core)

add_executable(test03_1 test_transform.cpp)

target_include_directories(test03_1 PUBLIC
        ${EXTERNAL}/glfw/include
)

target_link_libraries(test03_1 PUBLIC
        OpenGL32
        ${EXTERNAL}/glfw/lib-mingw-w64/glfw3.dll
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3.a
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3dll.a
        renderer_math
        renderer_core
)

