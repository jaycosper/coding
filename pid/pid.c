
/*
 * PID - porportional, integral, differential controller
 */

#include <stdint.h>
#include <stdio.h>
//#include <sys/time.h>
//#include <time.h>
#include "pid.h"
#include "assert.h"

/*working variables*/
simple_pid_t pid_params;

unsigned long ms_cntr = 0;
unsigned long millis(void)
{
    unsigned long curr_ms_cntr = ms_cntr;
    ms_cntr += 200;
    return curr_ms_cntr++;
    /*
    struct timeval start, stop;
    double secs = 0;

    gettimeofday(&start, NULL);

    // Do stuff  here

    gettimeofday(&stop, NULL);
    //secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    secs = (double)(stop.tv_usec) / 1000000 + (double)(stop.tv_sec);
    printf("time taken %f\n",secs);
    return (unsigned long)secs;
    */
    /*
  char buffer[30];
  struct timeval tv;

  time_t curtime;

  gettimeofday(&tv, NULL);
  curtime=tv.tv_sec;

  strftime(buffer,30,"%m-%d-%Y  %T.",localtime(&curtime));
  printf("%s%ld\n",buffer,tv.tv_usec);

  return (unsigned long)tv.tv_usec;
  */
}

simple_pid_t pidGetParams(void)
{
    return pid_params;
}

void pidSetTunings(double Kp, double Ki, double Kd)
{
   pid_params.kp = Kp;
   pid_params.ki = Ki;
   pid_params.kd = Kd;
}

double pidCompute(void)
{
   /*How long since we last calculated*/
   unsigned long now = millis();
   double timeChange = (double)(now - pid_params.lastTime);

   /*Compute all the working error variables*/
   double error = pid_params.Setpoint - pid_params.Input;
   pid_params.errSum += (error * timeChange);
   double dErr = (error - pid_params.lastErr) / timeChange;

   /*Compute PID Output*/
   pid_params.Output = pid_params.kp * error + pid_params.ki * pid_params.errSum + pid_params.kd * dErr;

   /*Remember some variables for next time*/
   pid_params.lastErr = error;
   pid_params.lastTime = now;

   return pid_params.Output;
}

#ifdef REFERENCE_PID
 // http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-direction/
 /*working variables*/
 unsigned long lastTime;
 double Input, Output, Setpoint;
 double ITerm, lastInput;
 double kp, ki, kd;
 int SampleTime = 1000; //1 sec
 double outMin, outMax;
 bool inAuto = false;

 #define MANUAL 0
 #define AUTOMATIC 1

 #define DIRECT 0
 #define REVERSE 1
 int controllerDirection = DIRECT;

 void Compute()
 {
    if(!inAuto) return;
    unsigned long now = millis();
    int timeChange = (now - lastTime);
    if(timeChange>=SampleTime)
    {
       /*Compute all the working error variables*/
       double error = Setpoint - Input;
       ITerm+= (ki * error);
       if(ITerm > outMax) ITerm= outMax;
       else if(ITerm < outMin) ITerm= outMin;
       double dInput = (Input - lastInput);

       /*Compute PID Output*/
       Output = kp * error + ITerm- kd * dInput;
       if(Output > outMax) Output = outMax;
       else if(Output < outMin) Output = outMin;

       /*Remember some variables for next time*/
       lastInput = Input;
       lastTime = now;
    }
 }

 void SetTunings(double Kp, double Ki, double Kd)
 {
    if (Kp<0 || Ki<0|| Kd<0) return;

   double SampleTimeInSec = ((double)SampleTime)/1000;
    kp = Kp;
    ki = Ki * SampleTimeInSec;
    kd = Kd / SampleTimeInSec;

   if(controllerDirection ==REVERSE)
    {
       kp = (0 - kp);
       ki = (0 - ki);
       kd = (0 - kd);
    }
 }

 void SetSampleTime(int NewSampleTime)
 {
    if (NewSampleTime > 0)
    {
       double ratio  = (double)NewSampleTime
                       / (double)SampleTime;
       ki *= ratio;
       kd /= ratio;
       SampleTime = (unsigned long)NewSampleTime;
    }
 }

 void SetOutputLimits(double Min, double Max)
 {
    if(Min > Max) return;
    outMin = Min;
    outMax = Max;

    if(Output > outMax) Output = outMax;
    else if(Output < outMin) Output = outMin;

    if(ITerm > outMax) ITerm= outMax;
    else if(ITerm < outMin) ITerm= outMin;
 }

 void SetMode(int Mode)
 {
     bool newAuto = (Mode == AUTOMATIC);
     if(newAuto == !inAuto)
     {  /*we just went from manual to auto*/
         Initialize();
     }
     inAuto = newAuto;
 }

 void Initialize()
 {
    lastInput = Input;
    ITerm = Output;
    if(ITerm > outMax) ITerm= outMax;
    else if(ITerm < outMin) ITerm= outMin;
 }

 void SetControllerDirection(int Direction)
 {
    controllerDirection = Direction;
 }
 #endif