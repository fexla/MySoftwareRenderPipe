add_executable(test08_0 test_opencv.cpp)

target_link_libraries(test08_0 ${OpenCV_LIBS} renderer_math)

add_executable(test08_1 test_texture.cpp)

target_include_directories(test08_1 PUBLIC
        ${EXTERNAL}/glfw/include
)

target_link_libraries(test08_1
        ${OpenCV_LIBS}
        renderer_math
        renderer_core
        OpenGL32
        ${EXTERNAL}/glfw/lib-mingw-w64/glfw3.dll
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3.a
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3dll.a
)


