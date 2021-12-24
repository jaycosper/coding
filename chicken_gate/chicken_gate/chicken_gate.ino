#include <stdint.h>

constexpr uint8_t LIGHT_SENSOR_PIN = A0;
constexpr uint8_t SW_OPEN_PIN = 2;
constexpr uint8_t SW_CLOSED_PIN = 3;
constexpr uint8_t MTR_PWM1_PIN = 5;
constexpr uint8_t MTR_PWM2_PIN = 6;
constexpr uint8_t MTR_EN_PIN = 11;
constexpr uint8_t MTR_ENB_PIN = 12;
constexpr uint8_t MTR_DIAG_PIN = 10;
constexpr uint8_t MAN_SW_PIN = A1;
constexpr uint8_t MAN_JOYX_PIN = A2;
constexpr uint8_t MAN_JOYY_PIN = A3;

typedef enum
{
  dirClose = false,
  dirOpen = true
} direction_e;

typedef struct motor_s
{
  bool en;
  bool enb;
  int pwm1;
  int pwm2;
  bool diag;
} motor_t;

typedef struct motorState_s
{
  motor_t motor;
  direction_e dir;
} motorState_t;

static motorState_t myMotorState;

enum states_e {
    stIDLE,
    stOPENING,
    stOPEN,
    stCLOSING,
    stCLOSED,
    max_states
};

typedef struct _coop_sm_s_
{
    states_e currentState;
    bool swOpen;
    bool swClosed;
    bool dayTime;
    uint32_t eventTime;
    bool lightEvent;
    bool darkEvent;
} coop_sm_t;

static coop_sm_t sm;
constexpr uint32_t LIGHT_DETECT_VOLTAGE_THRESHOLD = 200;
constexpr uint32_t LIGHT_DETECT_TIME_THRESHOLD = 20; //60;

void printMotor(const motor_t rMotor)
{
  Serial.print("Motor.en: ");
  Serial.println(rMotor.en);
  Serial.print("Motor.enb: ");
  Serial.println(rMotor.enb);
  Serial.print("Motor.pwm1: ");
  Serial.println(rMotor.pwm1);
  Serial.print("Motor.pwm2: ");
  Serial.println(rMotor.pwm2);
  Serial.print("Motor.diag: ");
  Serial.println((rMotor.diag) ? "ON" : "OFF");
}

void printMotorState(const motorState_t rMotorState)
{
  printMotor(rMotorState.motor);
  Serial.print("MotorState.dir: ");
  Serial.println(rMotorState.dir);
}

void setMotor(motor_t &rMotor)
{
  digitalWrite(MTR_EN_PIN, rMotor.en);
  digitalWrite(MTR_ENB_PIN, rMotor.enb);
  analogWrite(MTR_PWM1_PIN, rMotor.pwm1);
  analogWrite(MTR_PWM2_PIN, rMotor.pwm2);
}

void disableMotor(motorState_t &rMotorState)
{
  rMotorState.motor.en = LOW;
  rMotorState.motor.enb = HIGH;
  rMotorState.motor.pwm1 = 0;
  rMotorState.motor.pwm2 = 0;
  rMotorState.dir = dirOpen;
  setMotor(rMotorState.motor);
}

bool getMotorStatus(motor_t &rMotor)
{
  rMotor.diag = digitalRead(MTR_DIAG_PIN);
  return rMotor.diag;
}

void driveMotor(motorState_t &rMotorState, direction_e dir, int dutyCycle)
{
  rMotorState.motor.en = HIGH;
  rMotorState.motor.enb = LOW;
  int tpwm = static_cast<int>(dutyCycle*255/100);
  rMotorState.dir = dir;
  rMotorState.motor.pwm1 = (rMotorState.dir == dirOpen) ? tpwm : 0;
  rMotorState.motor.pwm2 = (rMotorState.dir == dirOpen) ? 0: tpwm;
  setMotor(rMotorState.motor);
}

int detectSwitches(coop_sm_t &sm, const uint32_t timer)
{
  sm.swOpen = !digitalRead(SW_OPEN_PIN);
  sm.swClosed = !digitalRead(SW_CLOSED_PIN);
  int temp = (sm.swClosed) ? 1 << 1 : 0;
  temp |= (sm.swOpen) ? 1 : 0;
  return temp;
}

int detectDaytime(coop_sm_t &sm, const uint32_t timer)
{

  // reads the input on analog pin A0 (value between 0 and 1023)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  // We'll have a few threshholds, qualitatively determined
  if (analogValue < LIGHT_DETECT_VOLTAGE_THRESHOLD)
  {
    // detected dark
    if (sm.dayTime)
    {
      // its day
      if (!sm.darkEvent)
      {
        sm.darkEvent = true;
        sm.eventTime = timer;
      }
      sm.lightEvent = false;
      if ((timer - sm.eventTime) > LIGHT_DETECT_TIME_THRESHOLD)
      {
        sm.lightEvent = false;
        sm.darkEvent = false;
        sm.dayTime = false;
      }
    }
    else
    {
      // its night
      sm.lightEvent = false;
      sm.darkEvent = false;
    }
  }
  else
  {
    // detected light
    if (!sm.dayTime)
    {
      // its night
      if (!sm.lightEvent)
      {
        sm.lightEvent = true;
        sm.eventTime = timer;
      }
      sm.darkEvent = false;
      if ((timer - sm.eventTime) > LIGHT_DETECT_TIME_THRESHOLD)
      {
        sm.lightEvent = false;
        sm.darkEvent = false;
        sm.dayTime = true;
      }
    }
    else
    {
      // its day
      sm.lightEvent = false;
      sm.darkEvent = false;
    }
  }

  return analogValue;
}

uint32_t processStateMachine(coop_sm_t &sm)
{
  switch(sm.currentState)
  {
    case stIDLE:
      disableMotor(myMotorState);
      sm.currentState = stOPEN;
      break;
    case stOPENING:
      if (sm.swOpen)
      {
        disableMotor(myMotorState);
        sm.currentState = stOPEN;
      }
      else
      {
        driveMotor(myMotorState, dirOpen, 75);
      }
      break;
    case stOPEN:
      if (!sm.dayTime)
      {
        sm.currentState = stCLOSING;
      }
      break;
    case stCLOSING:
      if (sm.swClosed)
      {
        disableMotor(myMotorState);
        sm.currentState = stCLOSED;
      }
      else
      {
        driveMotor(myMotorState, dirClose, 75);
      }
      break;
    case stCLOSED:
      if (sm.dayTime)
      {
        sm.currentState = stOPENING;
      }
      break;
    default:
      sm.currentState= stIDLE;
      break;
  }

  Serial.print("state : ");
  Serial.println(sm.currentState);
  return 0;
}

void initSystem(void)
{
  sm.currentState = stIDLE;
  sm.eventTime = 0;

  uint32_t sw = detectSwitches(sm, 0);
  sm.swClosed = (sw & 0x2);
  sm.swOpen = (sw & 0x1);

  sm.lightEvent = false;
  sm.darkEvent = false;

  int lightValue = detectDaytime(sm, 0);
  if (lightValue > LIGHT_DETECT_VOLTAGE_THRESHOLD) sm.dayTime = true;
  else sm.dayTime = false;
}

void setup() {
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // Switches
  pinMode(SW_OPEN_PIN, INPUT_PULLUP);
  pinMode(SW_CLOSED_PIN, INPUT_PULLUP);
  // Motor
  pinMode(MTR_DIAG_PIN, INPUT);
  pinMode(MTR_EN_PIN, OUTPUT);
  pinMode(MTR_ENB_PIN, OUTPUT);
  pinMode(MTR_PWM1_PIN, OUTPUT);
  pinMode(MTR_PWM2_PIN, OUTPUT);
  disableMotor(myMotorState);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  initSystem();
}

void loop() {
  static bool ledState = HIGH;
  static uint32_t loopCntr = 0;

  static bool manualMode = false;
  int manSw = analogRead(MAN_SW_PIN);
  if (manSw < 50)
  {
    if (manualMode)
    {
      // manual -> automatic
      manualMode = false;
    }
    else
    {
      // automatic -> manual
      disableMotor(myMotorState);
      manualMode = true;
    }
  }

  int swState = detectSwitches(sm, loopCntr);
  Serial.print("swState reading: ");
  Serial.println(swState);

  int lightValue = detectDaytime(sm, loopCntr);

  Serial.print("light value: ");
  Serial.println(lightValue);

  if (manualMode)
  {
    // manual mode -- use joystick to move motor
    int manJX = analogRead(MAN_JOYX_PIN);
    int manJY = analogRead(MAN_JOYY_PIN);
    if (manJX < 100) driveMotor(myMotorState, dirOpen, 75);
    else if (manJX > 923) driveMotor(myMotorState, dirClose, 75);
    else disableMotor(myMotorState);
  }
  else
  {
    // process state machine
    processStateMachine(sm);
    printState(sm);
  }

  // toggle LED
  digitalWrite(LED_BUILTIN, ledState);
  ledState = !ledState;

  loopCntr++;
  delay(500);
}

void printState(const coop_sm_t sm)
{
  Serial.print("sm.currentState: ");
  Serial.println(sm.currentState);
  Serial.print("sm.swOpen: ");
  Serial.println(sm.swOpen);
  Serial.print("sm.swClosed: ");
  Serial.println(sm.swClosed);
  Serial.print("sm.dayTime: ");
  Serial.println(sm.dayTime);
  Serial.print("sm.eventTime: ");
  Serial.println(sm.eventTime);
  Serial.print("sm.lightEvent: ");
  Serial.println(sm.lightEvent);
  Serial.print("sm.darkEvent: ");
  Serial.println(sm.darkEvent);
  printMotorState(myMotorState);
}