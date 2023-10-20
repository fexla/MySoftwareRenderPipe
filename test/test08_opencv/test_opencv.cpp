//
// Created by q on 2023/10/20.
//
#include <opencv2/opencv.hpp>
#include "iostream"

const std::string filepath = "E:\\Projects\\Exercise1_SoftwareRenderPipe/lappland.png";

int main() {
    cv::Mat image_data = cv::imread(filepath, cv::IMREAD_UNCHANGED);

    auto width = image_data.cols;
    auto height = image_data.rows;

    std::cout << "width:\t" << width << "height:\t" << height << std::endl;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (!image_data.at<cv::Vec4b>(i, j)[3]) {
                image_data.at<cv::Vec4b>(i, j) = {};
            }
        }
    }
    cv::imshow("picture", image_data);
    cv::waitKey(0);
}