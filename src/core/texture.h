//
// Created by LEI XU on 4/27/19.
//

#ifndef MYSOFTWARERENDERPIPE_TEXTURE_H
#define MYSOFTWARERENDERPIPE_TEXTURE_H

//#ifndef STB
//#define STB
//#define STB_IMAGE_IMPLEMENTATION
//
//#include "stb_image.h"
//#undef STB_IMAGE_IMPLEMENTATION
//#endif
#include "stb_image.h"
#include "string"
#include "color.h"

//struct color {
//    unsigned char r, g, b, a;
//};

class Texture {
private:
    const unsigned char *idata;
    int width, height, channels;

public:
    Texture() : idata(), width(0), height(0) {}

    Texture(const std::string &name) {
        loadFromFile(name);
    }

    void loadFromFile(const std::string &name) {
        if(name.empty()) {
            width = 1;
            height = 1;
            channels = 4;
            idata = new unsigned char[4];
            return;
        }
        idata = stbi_load(name.c_str(), &width, &height, &channels, 0);
//        image_data = cv::imread(name, cv::IMREAD_UNCHANGED);
//        cv::cvtColor(image_data, image_data, cv::COLOR_BGRA2RGBA);
//        width = image_data.cols;
//        height = image_data.rows;
    }


    color getColor(float u, float v) const {
//        auto u_img = u * width;
//        auto v_img = (1 - v) * height;
//        v_img = std::max(0.f, v_img - 1);
//        auto color = image_data.at<cv::Vec4b>(v_img, u_img);
//        return {color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f, color[3] / 255.0f,};


        int u_img = static_cast<int>(u * width);
        int v_img = static_cast<int>((1 - v) * height);
        int pixel_index = 3 * (v_img * width + u_img);

        // 获取RGB值
        unsigned char r = idata[pixel_index];
        unsigned char g = idata[pixel_index + 1];
        unsigned char b = idata[pixel_index + 2];

        return color{r / 255.0f, g / 255.0f, b / 255.0f, 1};
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }
};

#endif //MYSOFTWARERENDERPIPE_TEXTURE_H
