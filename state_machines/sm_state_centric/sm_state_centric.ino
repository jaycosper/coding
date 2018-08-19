
// Pinout
#define GRN_PIN 13
#define YEL_PIN 14
#define RED_PIN 15
#define GO_BUTTON_PIN 16

// SM defines
enum
{
  stGreen = 0,
  stYellow,
  stRed,
};

#define LED_GREEN   GRN_PIN
#define LED_YELLOW  YEL_PIN
#define LED_RED     RED_PIN
#define LED_ON  HIGH
#define LED_OFF LOW

#define BUTTON_GO   GO_BUTTON_PIN

// Global objects
// Create an IntervalTimer object
IntervalTimer myTimer;
#define TIMER_INTERVAL_US   100000
#define YELLOW_TIMEOUT_COUNT 10

typedef struct _stopLightCtx_t
{
  uint32_t state;
  bool bStopCondition;
  bool bGoCondition;
  bool bYellowTimeout;
  uint32_t yellowCount;
  bool bGoButton, bGoButtonDelay;
  bool bStopButton, bStopButtonDelay;
} stopLightCtx_t;

stopLightCtx_t gCtx;

void initContext(void)
{
  gCtx.state = stGreen;
  gCtx.bStopCondition = false;
  gCtx.bGoCondition = false;
  gCtx.bYellowTimeout = true;
  gCtx.yellowCount = 0;
  gCtx.bGoButtonDelay = false;
  gCtx.bStopButtonDelay = false;
  gCtx.bGoButton = false;
  gCtx.bStopButton = false;
}

void initLEDs(void)
{
  pinMode(GRN_PIN, OUTPUT);
  pinMode(YEL_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  setLEDOn(LED_GREEN);
  setLEDOff(LED_YELLOW);
  setLEDOff(LED_RED);
}

void initButtons(void)
{
  pinMode(GO_BUTTON_PIN, INPUT);
  pinMode(STOP_BUTTON_PIN, INPUT);
}

void setup()
{
  Serial.begin(115200);
  initLEDs();
  initButtons();
  initContext();
  myTimer.begin(isrTimerTick, TIMER_INTERVAL_US);
  Serial.print("Setup complete!\n");
}

void setLEDOn(uint32_t led)
{
  digitalWrite(led, LED_ON);
}

void setLEDOff(uint32_t led)
{
  digitalWrite(led, LED_OFF);
}

bool readButton(uint32_t button)
{
  uint32_t val;
  val = digitalRead(button);
  if (val)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void isrTimerTick(void)
{
  // debounce buttons
  gCtx.bGoButtonDelay = gCtx.bGoButton;
  gCtx.bStopButtonDelay = gCtx.bStopButton;
  gCtx.bGoButton = readButton(BUTTON_GO);
  gCtx.bStopButton = readButton(BUTTON_STOP);

  if (gCtx.bGoButton == gCtx.bGoButtonDelay)
  {
    gCtx.bGoCondition = !gCtx.bGoButton;
    gCtx.bStopCondition = gCtx.bGoButton;
  }

  if (gCtx.bYellowTimeout == false)
  {
    gCtx.yellowCount++;
    if (gCtx.yellowCount == YELLOW_TIMEOUT_COUNT)
    {
      gCtx.yellowCount = 0;
      gCtx.bYellowTimeout = true;
    }
  }
}

void loop()
{
  switch (gCtx.state)
  {
    case stGreen:
      if (gCtx.bStopCondition)
      {
        Serial.print("TRANSITION: green to yellow state\n");
        gCtx.state = stYellow;
        setLEDOff(LED_GREEN);
        setLEDOn(LED_YELLOW);
        setLEDOff(LED_RED);
        gCtx.bYellowTimeout = false;
      }
      break;
    case stYellow:
      if (gCtx.bYellowTimeout)
      {
        Serial.print("TRANSITION: yellow to red state\n");
        gCtx.state = stRed;
        setLEDOff(LED_GREEN);
        setLEDOff(LED_YELLOW);
        setLEDOn(LED_RED);
      }
      break;
    case stRed:
      if (gCtx.bGoCondition)
      {
        Serial.print("TRANSITION: red to green state\n");
        gCtx.state = stGreen;
        setLEDOn(LED_GREEN);
        setLEDOff(LED_YELLOW);
        setLEDOff(LED_RED);
      }
      break;
    default:
      Serial.print("ERROR: unhandled state!\n");
      while(1);
      break;
  }
}
