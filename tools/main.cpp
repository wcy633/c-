#include "detection_config.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include "camera.hpp"
#include "contour_task.hpp"
#include "pid_task.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

int main(int argc, char** argv)
{
    Camera cam(0);
    cv::Mat source;

    fs::path output_dir = fs::current_path() / "output";
    std::error_code err;
    fs::create_directories(output_dir, err);
    if (err)
    {
        std::cerr << "创建output文件夹失败：" << err.message() << std::endl;
        return 1;
    }

    // 初始化两个PID：水平X、竖直Y
    PID pid_x(0.08, 0.001, 0.02, 30.0);
    PID pid_y(0.08, 0.001, 0.02, 30.0);

    while(true)
    {
        if(!cam.read(source))
        {
            std::cerr << "读取相机帧失败\n";
            continue;
        }

        double img_cx = source.cols / 2.0;
        double img_cy = source.rows / 2.0;
        cv::line(source, cv::Point(img_cx, 0), cv::Point(img_cx, source.rows), cv::Scalar(255,255,255),1);
        cv::line(source, cv::Point(0, img_cy), cv::Point(source.cols, img_cy), cv::Scalar(255,255,255),1);

        cv::Mat hsv;
        cv::cvtColor(source, hsv, cv::COLOR_BGR2HSV);

        cv::Mat red_low, red_high, red_mask;
        cv::inRange(hsv, detection_config::red_low_min, detection_config::red_low_max, red_low);
        cv::inRange(hsv, detection_config::red_high_min, detection_config::red_high_max, red_high);
        cv::bitwise_or(red_low, red_high, red_mask);

        cv::Mat blue_mask;
        cv::inRange(hsv, detection_config::blue_min, detection_config::blue_max, blue_mask);

        cv::Mat green_mask;
        cv::inRange(hsv, detection_config::green_min, detection_config::green_max, green_mask);

        auto red_targets  = findAndDrawContours(red_mask, source, cv::Scalar(0, 0, 255));
        auto blue_targets = findAndDrawContours(blue_mask, source, cv::Scalar(255, 0, 0));
        auto green_targets= findAndDrawContours(green_mask, source, cv::Scalar(0, 255, 0));

        // 我们优先追踪第一个红色目标（比赛常用：锁定单一目标）
        if (!red_targets.empty())
        {
            auto& t = red_targets[0];
            double off_x = t.center.x - img_cx;
            double off_y = t.center.y - img_cy;

            double out_x = pid_x.calc(off_x);
            double out_y = pid_y.calc(off_y);

            std::cout << "==== 追踪红色目标 ====\n";
            std::cout << "偏移 X:" << off_x << "  PID输出X:" << out_x << "\n";
            std::cout << "偏移 Y:" << off_y << "  PID输出Y:" << out_y << "\n";
        }
        else
        {
            // 丢失目标，重置PID积分，防止积分累积炸掉
            pid_x.reset();
            pid_y.reset();
            std::cout << "未找到红色目标，PID已重置\n";
        }

        cv::imshow("source", source);
        cv::imshow("red_mask", red_mask);
        cv::imshow("blue_mask", blue_mask);
        cv::imshow("green_mask", green_mask);

        int key = cv::waitKey(1);
        if (key == 27)
        {
            break;
        }
        if (key == 's' || key == 'S')
        {
            bool red_saved = cv::imwrite((output_dir / "red_mask.png").string(), red_mask);
            bool green_saved = cv::imwrite((output_dir / "green_mask.png").string(), green_mask);
            bool blue_saved = cv::imwrite((output_dir / "blue_mask.png").string(), blue_mask);
            if (!red_saved || !blue_saved || !green_saved)
            {
                std::cerr << "保存mask图片失败！\n";
            }
            else
            {
                std::cout << "已保存三张mask到output文件夹！\n";
            }
        }
    }

    return 0;
}