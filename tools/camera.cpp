#include "camera.hpp"
Camera::Camera(int device_id){
    cap_.open(device_id);
    is_opened_=cap_.isOpened();
    if(!is_opened_){
        std::cerr<<"cuowu"<<device_id<<std::endl;
        }
}
Camera::~Camera(){
    if(cap_.isOpened()){
        cap_.release();
    }
}
bool Camera::read(cv::Mat &frame){
    if(!is_opened_)return false;
    bool ok=cap_.read(frame);
    return ok&&!frame.empty();
}