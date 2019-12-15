/*
  Auto H20 - auto watering system to Christmas trees
  Jay Cosper
  20191214
*/

/* Pin definitions */
const int waterLevelPin = 0;
const int faultPin =  3;
const int sourceLowLedPin =  4;
const int sourceLowDetectPin =  5;
const int pumpCtrl = 2;

/* constants */
const int LED_ON = 1;
const int LED_OFF = 0;
const int PUMP_ON = 1;
const int PUMP_OFF = 0;
const int SENSOR_CHECK_RATE = 1000; /* main loop rate in ms */
const int PUMP_TIMEOUT_VALUE = 30; /* max time in SENSOR_CHECK_RATE units pump can be on */
const int WATER_LEVEL_LOW_VALUE = 150;
const int WATER_LEVEL_HIGH_VALUE = 170;

/* global variables */
int pumpState;
int pumpTimeout;

/* prototypes */
void faultState(void);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // initialize pin direction
  pinMode(faultPin, OUTPUT);
  pinMode(sourceLowLedPin, OUTPUT);
  pinMode(pumpCtrl, OUTPUT);

  pinMode(sourceLowDetectPin, INPUT);

  pumpState = PUMP_OFF;

  digitalWrite(faultPin, LED_OFF);
  digitalWrite(sourceLowLedPin, LED_OFF);
  digitalWrite(pumpCtrl, pumpState);
}

// the loop routine runs over and over again forever:
void loop() {

  int waterLevel;
  int sourceLowDetect;

  Serial.println("Entering main loop");

  /* read the source water level switch */
  sourceLowDetect = digitalRead(sourceLowDetectPin);
  Serial.print("sourceLowDetect: ");
  Serial.println(sourceLowDetect);

  /*
   * make sure that:
   * 1. the pump has not been running too long, and
   */
  if (pumpState == PUMP_ON)
  {
    pumpTimeout++;
    Serial.print("pumpTimeout: ");
    Serial.println(pumpTimeout);
    if (pumpTimeout > PUMP_TIMEOUT_VALUE)
    {
      faultState();
    }
  }
  else
  {
    pumpTimeout = 0;
  }

  /*
   * 2. water in present in the source tank
   */
  if (!sourceLowDetect)
  {

    /* read the analog water sensor */
    waterLevel = analogRead(waterLevelPin);

    /* if pump is ON, check against HIGH level */
    Serial.print("waterLevel: ");
    Serial.println(waterLevel);
    Serial.print("pumpState: ");
    Serial.println(pumpState);
    if (waterLevel <= WATER_LEVEL_LOW_VALUE)
    {
      pumpState = PUMP_ON;
    }
    /* if pump is OFF, check against LOW level */
    else if (waterLevel >= WATER_LEVEL_HIGH_VALUE)
    {
      pumpState = PUMP_OFF;
    }
    else
    {
      Serial.print("waterLevel midrange: ");
      Serial.println(waterLevel);
    }

    /* set the pump state */
    digitalWrite(pumpCtrl, pumpState);
  }
  else
  {
    /* water source is low */
    Serial.print("sourceLowDetect fault: ");
    Serial.println(sourceLowDetect);
    faultState();
  }


  /* delay between main loop runs */
  delay(SENSOR_CHECK_RATE);
}

void faultState(void)
{
  Serial.print("FAULT: pumpState ");
  Serial.print(pumpState);
  Serial.print(" pumpTimeout: ");
  Serial.println(pumpTimeout);
  pumpState = PUMP_OFF;
  digitalWrite(faultPin, LED_ON);
  digitalWrite(pumpCtrl, pumpState);
  while(1); /* trap -- wait for reset */
}