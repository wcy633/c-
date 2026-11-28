#pragma once

#include <opencv2/core.hpp>
#include "color range.hpp"
#include <string>
struct ColorSegmentResult {
    cv::Mat mask;
    cv::Mat segmented_image;
};
namespace  algorithm{
    ColorSegmentResult color_segment(const cv::Mat& image, const config::ColorRange& color_range) ;
}