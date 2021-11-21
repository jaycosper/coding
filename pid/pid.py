# pid.py
import matplotlib.pyplot as plt

class pid_ctrlr:

    def __init__(self):
        self.errLast = 0
        self.errSum = 0
        self.currPos = 0

    def pid_setParams(self, kp, kd, ki):
        self.kp = kp
        self.kd = kd
        self.ki = ki

    def pid_compute(self, setPoint):
        # currPos = pid_compute(errSum, errLast, sp, currPos)
    #def pid_compute(errSum, errLast, Setpoint, position):
        timeDelta = 1
        # Compute all the working error variables
        #error = Setpoint - position
        error = setPoint - self.currPos
        errSum = (error * timeDelta) + self.errSum
        dErr = (error - self.errLast) / timeDelta

        # Compute PID Output
        Output = self.kp * error + self.ki * errSum + self.kd * dErr

        # Remember some variables for next time
        self.errLast = error
        #return Output
        self.currPos = Output
        return Output



# signal gen
time = []
setpoint = []
position = []
totaltime = 150
Kp = 0.6
Kd = 0
Ki = 0

# PID instance
ctrlr = pid_ctrlr()
# PID setup
ctrlr.pid_setParams(Kp, Kd, Ki)

# gather data
for t in range(totaltime):
    sp = 1
    if t < 10:
        sp = 0
    if t > 100:
        sp = 0.75

    currPos = ctrlr.pid_compute(sp)
    time.append(t)
    setpoint.append(sp)
    position.append(currPos)


plt.plot(time, setpoint, position)
plt.xlabel('time')
plt.ylabel('position')
plt.show()


#/*working variables*/
#unsigned long lastTime;
#double Input, Output, Setpoint;
#double ITerm, lastInput;
#double kp, ki, kd;
#int SampleTime = 1000; //1 sec
#double outMin, outMax;
#bool inAuto = false;
#
##define MANUAL 0
##define AUTOMATIC 1
#
##define DIRECT 0
##define REVERSE 1
#int controllerDirection = DIRECT;
#
#void Compute()
#{
#   if(!inAuto) return;
#   unsigned long now = millis();
#   int timeChange = (now - lastTime);
#   if(timeChange>=SampleTime)
#   {
#      /*Compute all the working error variables*/
#      double error = Setpoint - Input;
#      ITerm+= (ki * error);
#      if(ITerm > outMax) ITerm= outMax;
#      else if(ITerm < outMin) ITerm= outMin;
#      double dInput = (Input - lastInput);
#
#      /*Compute PID Output*/
#      Output = kp * error + ITerm- kd * dInput;
#      if(Output > outMax) Output = outMax;
#      else if(Output < outMin) Output = outMin;
#
#      /*Remember some variables for next time*/
#      lastInput = Input;
#      lastTime = now;
#   }
#}
#
#void SetTunings(double Kp, double Ki, double Kd)
#{
#   if (Kp<0 || Ki<0|| Kd<0) return;
#
#  double SampleTimeInSec = ((double)SampleTime)/1000;
#   kp = Kp;
#   ki = Ki * SampleTimeInSec;
#   kd = Kd / SampleTimeInSec;
#
#  if(controllerDirection ==REVERSE)
#   {
#      kp = (0 - kp);
#      ki = (0 - ki);
#      kd = (0 - kd);
#   }
#}
#
#void SetSampleTime(int NewSampleTime)
#{
#   if (NewSampleTime > 0)
#   {
#      double ratio  = (double)NewSampleTime
#                      / (double)SampleTime;
#      ki *= ratio;
#      kd /= ratio;
#      SampleTime = (unsigned long)NewSampleTime;
#   }
#}
#
#void SetOutputLimits(double Min, double Max)
#{
#   if(Min > Max) return;
#   outMin = Min;
#   outMax = Max;
#
#   if(Output > outMax) Output = outMax;
#   else if(Output < outMin) Output = outMin;
#
#   if(ITerm > outMax) ITerm= outMax;
#   else if(ITerm < outMin) ITerm= outMin;
#}
#
#void SetMode(int Mode)
#{
#    bool newAuto = (Mode == AUTOMATIC);
#    if(newAuto == !inAuto)
#    {  /*we just went from manual to auto*/
#        Initialize();
#    }
#    inAuto = newAuto;
#}
#
#void Initialize()
#{
#   lastInput = Input;
#   ITerm = Output;
#   if(ITerm > outMax) ITerm= outMax;
#   else if(ITerm < outMin) ITerm= outMin;
#}
#
#void SetControllerDirection(int Direction)
#{
#   controllerDirection = Direction;
#}