#include "color_segment_task.hpp"
#include <opencv2/imgproc.hpp>
namespace algorithm {

ColorSegmentResult color_segment(const cv::Mat& image, const config::ColorRange& color_range) {
    if (image.empty()) {
        return {};
    }

    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    cv::Mat mask;
    cv::inRange(hsv, color_range.min, color_range.max, mask);

    cv::Mat segmented_image;
    cv::bitwise_and(image, image, segmented_image, mask);

    return {mask, segmented_image};
}

}