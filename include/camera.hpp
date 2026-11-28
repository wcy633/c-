#ifndef canerahpp
#define camerahpp
#include<opencv2/opencv.hpp>
#include<iostream>
class Camera{
    public:
    Camera(int device_id=0);
    ~Camera();
    bool read(cv::Mat &frame);
private:
    cv::VideoCapture cap_;
    bool is_opened_;
};
#endif