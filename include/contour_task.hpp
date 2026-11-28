#ifndef CONTOUR_TASK_HPP
#define CONTOUR_TASK_HPP

#include <opencv2/opencv.hpp>
#include <vector>

// 存储单个目标信息：中心点、面积、绘制颜色
struct TargetInfo
{
    cv::Point2f center;
    double area;
    cv::Scalar box_color;
};

// 输入mask，在原图画框，返回所有合格目标列表
std::vector<TargetInfo> findAndDrawContours(cv::Mat& mask, cv::Mat& src, cv::Scalar box_color);

#endif