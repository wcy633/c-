#pragma once
#include <opencv2/core.hpp>

namespace detection_config {

// OpenCV HSV: H is 0..179; S and V are 0..255.
// Red crosses the hue scale boundary, so use two ranges.
inline const cv::Scalar red_low_min(0, 90, 60);
inline const cv::Scalar red_low_max(10, 255, 255);
inline const cv::Scalar red_high_min(170, 90, 60);
inline const cv::Scalar red_high_max(179, 255, 255);

inline const cv::Scalar blue_min(95, 80, 50);
inline const cv::Scalar blue_max(135, 255, 255);

inline const cv::Scalar green_min (35,  60, 50);
inline const cv::Scalar green_max (85, 255, 255);
} // namespace detection_config