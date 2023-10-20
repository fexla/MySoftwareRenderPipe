add_executable(test08_0 test_opencv.cpp)

target_link_libraries(test08_0 ${OpenCV_LIBS} renderer_math)