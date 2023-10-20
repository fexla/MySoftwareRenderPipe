//
// Created by LEI XU on 4/27/19.
//

#ifndef MYSOFTWARERENDERPIPE_TEXTURE_H
#define MYSOFTWARERENDERPIPE_TEXTURE_H

#include <opencv2/opencv.hpp>
#include "color.h"

class Texture {
private:
    cv::Mat image_data;
    int width, height;

public:
    Texture() : image_data(), width(0), height(0) {}

    Texture(const std::string &name) {
        loadFromFile(name);
    }

    void loadFromFile(const std::string &name) {
        image_data = cv::imread(name, cv::IMREAD_UNCHANGED);
        cv::cvtColor(image_data, image_data, cv::COLOR_BGRA2RGBA);
        width = image_data.cols;
        height = image_data.rows;
    }


    color getColor(float u, float v) const {
        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        v_img = std::max(0.f, v_img - 1);
        auto color = image_data.at<cv::Vec4b>(v_img, u_img);
        return {color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f, color[3] / 255.0f,};
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }
};

#endif //MYSOFTWARERENDERPIPE_TEXTURE_H
