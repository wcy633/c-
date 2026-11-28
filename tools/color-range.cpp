#include "color range.hpp"

namespace config {

ColorConfig get_color_config() {
    ColorConfig config;

    config.red_low = {
        "red_low",
        cv::Scalar(0, 90, 60),
        cv::Scalar(10, 255, 255),
        cv::Scalar(0, 0, 255)
    };

    config.red_high = {
        "red_high",
        cv::Scalar(170, 90, 60),
        cv::Scalar(179, 255, 255),
        cv::Scalar(0, 0, 255)
    };

    config.blue = {
        "blue",
        cv::Scalar(95, 80, 50),
        cv::Scalar(135, 255, 255),
        cv::Scalar(255, 0, 0)
    };
    
    config.green={
        "green",
        cv::Scalar(40,90,70),
        cv::Scalar(80,255,230),
        cv::Scalar(0,255,0)
    };
    
    return config;
}

}