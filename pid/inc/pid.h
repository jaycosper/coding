/*
 * PID - porportional, integral, differential controller
 */

#ifndef __PID_H__
#define __PID_H__

#include <stdint.h>

typedef struct simple_pid_s
{
    unsigned long lastTime;
    double Input, Output, Setpoint;
    double errSum, lastErr;
    double kp, ki, kd;
} simple_pid_t;

simple_pid_t pidGetParams(void);
void pidSetTunings(double Kp, double Ki, double Kd);
double pidCompute(void);

#endif // __PID_H__
