add_executable(test01 main.cpp)

target_include_directories(test01 PUBLIC
        ${EXTERNAL}/glfw/include
)

target_link_libraries(test01 PUBLIC
        OpenGL32
        ${EXTERNAL}/glfw/lib-mingw-w64/glfw3.dll
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3.a
        ${EXTERNAL}/glfw/lib-mingw-w64/libglfw3dll.a
)

