#include "image_source.hpp"

namespace device {

cv::Mat readImage(const std::string& image_path) {
    cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Error: Could not read the image from path: " << image_path << std::endl;
    }
    return image;
}

}