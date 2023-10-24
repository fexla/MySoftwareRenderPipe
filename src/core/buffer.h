//
// Created by q on 2023/10/20.
//

#ifndef MYSOFTWARERENDERPIPE_BUFFER_H
#define MYSOFTWARERENDERPIPE_BUFFER_H

#include <cstddef>

#include "vector"

/**
 * 二维缓存
 * @tparam DataType 数据类型
 */

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

private:
    unsigned int width, height;
    std::vector<DataType> data;
};

#endif //MYSOFTWARERENDERPIPE_BUFFER_H
