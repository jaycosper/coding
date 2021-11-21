/*
 * Fake Floating Point Numbers
 * Implementation and test
 *
 */

#include <stdio.h>
#include "pid.h"

void dumpPIDParams(simple_pid_t params)
{
    printf("kp: %f\n", params.kp);
    printf("ki: %f\n", params.ki);
    printf("kd: %f\n", params.kd);
    printf("lastTime: %lu\n", params.lastTime);
    printf("Input: %f Output: %f Setpoint: %f\n", params.Input, params.Output, params.Setpoint);
    printf("errSum: %f lastErr: %f\n", params.errSum, params.lastErr);
}

int main(void)
{
    simple_pid_t pid_ctrl;
    pid_ctrl.kp = 1;
    pid_ctrl.ki = 2;
    pid_ctrl.kd = 3;
    pidSetTunings(pid_ctrl.kp, pid_ctrl.ki, pid_ctrl.kd);
    pidCompute();
    dumpPIDParams(pid_ctrl);

    return 0; // Ctest uses return 0 for pass
}
