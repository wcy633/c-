#pragma once
#include <opencv2/opencv.hpp>
#include <string>

namespace device {
    cv::Mat readImage(const std::string& image_path);
}