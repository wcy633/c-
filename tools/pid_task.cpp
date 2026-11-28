#include "pid_task.hpp"
#include <algorithm>

double PID::calc(double err)
{
    double p = Kp * err;
    err_sum += err;
    double i = Ki * err_sum;
    double d = Kd * (err - last_err);

    double out = p + i + d;
    last_err = err;

    // 限幅
    out = std::clamp(out, -max_out, max_out);
    return out;
}

void PID::reset()
{
    err_sum = 0.0;
    last_err = 0.0;
}