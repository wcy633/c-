#include "contour_task.hpp"
#include <vector>

std::vector<TargetInfo> findAndDrawContours(cv::Mat& mask, cv::Mat& src, cv::Scalar box_color)
{
    std::vector<TargetInfo> target_list;

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::Mat mask_clean;
    cv::morphologyEx(mask, mask_clean, cv::MORPH_OPEN, kernel);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(mask_clean, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (auto& cnt : contours)
    {
        double area = cv::contourArea(cnt);
        if (area < 20)
        {
            continue;
        }
        cv::Rect rect = cv::boundingRect(cnt);
        float w = rect.width;
        float h = rect.height;
        float ratio = w / h;
        if (ratio < 0.3 || ratio > 3.0)
        {
            continue;
        }

        // 计算矩形中心点
        float cx = rect.x + rect.width / 2.0f;
        float cy = rect.y + rect.height / 2.0f;
        cv::Point2f center(cx, cy);

        // 画外接矩形
        cv::rectangle(src, rect, box_color, 2);
        // 在中心点画实心小圆点
        cv::circle(src, center, 4, box_color, -1);

        // 存入目标列表
        TargetInfo t;
        t.center = center;
        t.area = area;
        t.box_color = box_color;
        target_list.push_back(t);
    }

    return target_list;
}