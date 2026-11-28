#ifndef PID_TASK_HPP
#define PID_TASK_HPP

struct PID
{
    double Kp;
    double Ki;
    double Kd;

    double err_sum = 0.0;
    double last_err = 0.0;

    double max_out;  // 输出限幅，防止速度爆炸

    PID(double p, double i, double d, double max_o)
        : Kp(p), Ki(i), Kd(d), max_out(max_o)
    {}

    double calc(double err);
    void reset();
};

#endif