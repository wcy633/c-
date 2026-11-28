#pragma once

#include <opencv2/core.hpp>

#include <string>

namespace config {

    struct ColorRange {
        std::string name;
        cv::Scalar min;
        cv::Scalar max;
        cv::Scalar draw_color;
    };

    struct ColorConfig{

        ColorRange red_low;
        ColorRange red_high;
        ColorRange blue;
        ColorRange green;
    };

    ColorConfig get_color_config();


}