
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

enum
{
  evtNone = 0,
  evtButtonPush,
  evtYTimeout,
  evtButtonRelease,
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
  bool bButtonPrevious;
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
  gCtx.bGoButton = false;
  gCtx.bButtonPrevious = false;
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
  uint32_t event = evtNone;

  // debounce buttons
  gCtx.bGoButtonDelay = gCtx.bGoButton;
  gCtx.bGoButton = readButton(BUTTON_GO);

  if (gCtx.bGoButton == gCtx.bGoButtonDelay)
  {
    // button state stable and debounced
    gCtx.bGoCondition = !gCtx.bGoButton;
    gCtx.bStopCondition = gCtx.bGoButton;
    if (gCtx.bGoButton != gCtx.bButtonPrevious)
    {
      // change in button state
      if (gCtx.bGoButton) /* 0->1 */ event = evtButtonPush;
      else /* !gCtx.bGoButton 1->0 */ event = evtButtonRelease;
      // store off value
      gCtx.bButtonPrevious = gCtx.bGoButton;
    }
  }

  if (gCtx.bYellowTimeout == false)
  {
    gCtx.yellowCount++;
    if (gCtx.yellowCount == YELLOW_TIMEOUT_COUNT)
    {
      gCtx.yellowCount = 0;
      gCtx.bYellowTimeout = true;
      event = evtYTimeout;
    }
  }
  if (event != evtNone)
  {
    Serial.print("EVENT: ");
    Serial.print(event);
    Serial.print("\n");
    eventHandler(event);
  }
}

void eventHandler(uint32_t event)
{
  setLEDOff(LED_GREEN);
  setLEDOff(LED_YELLOW);
  setLEDOff(LED_RED);
  switch(event)
  {
    case evtNone:
      // nothing to report
      break;
    case evtButtonPush:
      if (gCtx.state == stGreen)
      {
        Serial.print("TRANSITION: green to yellow state\n");
        gCtx.state = stYellow;
        setLEDOn(LED_YELLOW);
        gCtx.bYellowTimeout = false;
      }
      break;
    case evtYTimeout:
      if (gCtx.state == stYellow)
      {
        Serial.print("TRANSITION: yellow to red state\n");
        gCtx.state = stRed;
        setLEDOn(LED_RED);
      }
      break;
    case evtButtonRelease:
      if (gCtx.state == stRed)
      {
        Serial.print("TRANSITION: red to green state\n");
        gCtx.state = stGreen;
        setLEDOn(LED_GREEN);
      }
      break;
    default:
      Serial.print("ERROR: unhandled event!\n");
      while(1);
      break;
  }

}

void loop()
{
  // nothing in main loop
}
