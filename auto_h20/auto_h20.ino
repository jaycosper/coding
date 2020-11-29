/*
  Auto H20 - auto watering system for Christmas trees
  Jay Cosper
  20191214
*/
#define WATER_LEVEL_SENSORS 2
#define LOWER_WATER_SENSOR 0
#define UPPER_WATER_SENSOR 1

/* Pin definitions */
// These just happen to be the same as the index
#define LOWER_SENSOR_PIN 0
#define UPPER_SENSOR_PIN 1

const int waterLevelPin[WATER_LEVEL_SENSORS] = {LOWER_SENSOR_PIN, UPPER_SENSOR_PIN};
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
const int WATER_LEVEL_SWITCHPOINT = 512;

/* global variables */
int pumpState;
int pumpTimeout;

/* prototypes */
void faultState(void);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);

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

  int waterLevel[WATER_LEVEL_SENSORS];
  bool bWaterLevelSw[WATER_LEVEL_SENSORS];
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
    waterLevel[LOWER_WATER_SENSOR]= analogRead(waterLevelPin[LOWER_SENSOR_PIN]);
    waterLevel[UPPER_WATER_SENSOR]= analogRead(waterLevelPin[UPPER_SENSOR_PIN]);
    /* translate to binary */
    /* Active (blocked) sensor is pulled high */
    for (int i = 0; i < WATER_LEVEL_SENSORS; i++)
    {
      bWaterLevelSw[i] = true;
      if (waterLevel[i] <= WATER_LEVEL_SWITCHPOINT)
      {
        bWaterLevelSw[i] = false;
      }
    }

    /* if pump is ON, check against HIGH level */
    Serial.print("waterLevel: S0 ");
    Serial.print(waterLevel[LOWER_WATER_SENSOR]);
    Serial.print(" S1 ");
    Serial.println(waterLevel[UPPER_WATER_SENSOR]);
    Serial.print("pumpState: ");
    Serial.println(pumpState);

    /* Pump Case */
    if (!bWaterLevelSw[LOWER_WATER_SENSOR] && !bWaterLevelSw[UPPER_WATER_SENSOR]) {
      // neither switch active/blocked
      // empty, enable pump
      pumpState = PUMP_ON;
    } else if (bWaterLevelSw[LOWER_WATER_SENSOR] && !bWaterLevelSw[UPPER_WATER_SENSOR]) {
      // lower active/blocked, upper not active/blocked
      // normal water level, do nothing...
    } else if (!bWaterLevelSw[LOWER_WATER_SENSOR] && bWaterLevelSw[UPPER_WATER_SENSOR]) {
      // fault case
      // lower not active/blocked, upper active/blocked
      Serial.print("invalid sensor fault: S0 ");
      Serial.print(waterLevel[LOWER_WATER_SENSOR]);
      Serial.print(" S1 ");
      Serial.println(waterLevel[UPPER_WATER_SENSOR]);
      faultState();
    } else if (bWaterLevelSw[LOWER_WATER_SENSOR] && bWaterLevelSw[UPPER_WATER_SENSOR]) {
      // both switches active/blocked
      // full, shut off pump
      pumpState = PUMP_OFF;
    } else {
      // fault case -- should never see this
      Serial.print("impossible sensor fault: S0 ");
      Serial.print(waterLevel[LOWER_WATER_SENSOR]);
      Serial.print(" S1 ");
      Serial.println(waterLevel[UPPER_WATER_SENSOR]);
      faultState();
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

  /*
   * 3. delay between main loop runs
   */
  delay(SENSOR_CHECK_RATE);
}

void faultState(void)
{
  int waterLevel[WATER_LEVEL_SENSORS];
  Serial.print("FAULT: pumpState ");
  Serial.print(pumpState);
  Serial.print(" pumpTimeout: ");
  Serial.println(pumpTimeout);
  digitalWrite(faultPin, LED_ON);
  digitalWrite(pumpCtrl, PUMP_OFF);
  while(1)
  {
    /* trap -- wait for reset */
    delay(SENSOR_CHECK_RATE);
    waterLevel[LOWER_WATER_SENSOR]= analogRead(waterLevelPin[LOWER_SENSOR_PIN]);
    waterLevel[UPPER_WATER_SENSOR]= analogRead(waterLevelPin[UPPER_SENSOR_PIN]);
    Serial.print("waterLevel: S0 ");
    Serial.print(waterLevel[LOWER_WATER_SENSOR]);
    Serial.print(" S1 ");
    Serial.println(waterLevel[UPPER_WATER_SENSOR]);
  }
}
