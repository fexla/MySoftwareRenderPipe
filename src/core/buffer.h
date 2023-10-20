//
// Created by q on 2023/10/20.
//

#ifndef MYSOFTWARERENDERPIPE_BUFFER_H
#define MYSOFTWARERENDERPIPE_BUFFER_H

#include "vector"
#include <cstddef>

template<typename DataType>
class buffer2d {
public:
    buffer2d(unsigned int width, unsigned int height) : width(width), height(height), data(width * height) {
    }

    auto getSize() {
        return width * height;
    }

    auto getWidth() {
        return width;
    }

    auto getHeight() {
        return height;
    }

    DataType *operator[](size_t i) {
        return &data[0] + i * height;
    }
//    DataType &at(size_t x,size_t y) {
//        return data[y*width+x];
//    }

private:
    unsigned int width, height;
    std::vector<DataType> data;
};

#endif //MYSOFTWARERENDERPIPE_BUFFER_H
