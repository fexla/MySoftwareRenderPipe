add_executable(test00 main.cpp)

target_include_directories(test00 PUBLIC
        ${EXTERNAL}/glfw/include
)

target_link_libraries(test00 PUBLIC
        OpenGL32
        ${EXTERNAL}/glfw/lib-mingw-w64/glfw3.dll
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3.a
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3dll.a
)

