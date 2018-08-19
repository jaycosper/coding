
// Pinout
#define GRN_PIN 13
#define YEL_PIN 14
#define RED_PIN 15
#define GO_BUTTON_PIN 16

// Relay
#define RELAY_PIN 12

// SM defines
#define LED_GREEN   GRN_PIN
#define LED_YELLOW  YEL_PIN
#define LED_RED     RED_PIN
#define LED_ON  HIGH
#define LED_OFF LOW

#define BUTTON_GO   GO_BUTTON_PIN

#define RELAY       RELAY_PIN
#define RELAY_ON    HIGH
#define RELAY_OFF   LOW

enum
{
  stGreen   = 0,
  stYellow  = 1,
  stRed     = 2,
};

enum
{
  evtButtonPush     = 0,
  evtYTimeout       = 1,
  evtButtonRelease  = 2,
};

typedef struct _state_table_entry_
{
  uint32_t light;
  uint32_t goEvent;
  uint32_t stopEvent;
  uint32_t timeoutEvent;
} stateTableEntry_t;

stateTableEntry_t stateTable[] = {
  // Active LED   Event Go Button   Event Stop Button   Event Timeout
  {LED_GREEN,     stYellow,         stGreen,            stGreen}, // stGreen
  {LED_YELLOW,    stYellow,         stYellow,           stRed},   // stYellow
  {LED_RED,       stRed,            stGreen,            stRed},   // stRed
};

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

void initRelay(void)
{
  pinMode(RELAY_PIN, OUTPUT);
  setRelayOff();
}

void setup()
{
  Serial.begin(115200);
  initLEDs();
  initButtons();
  initRelay();
  initContext();
  myTimer.begin(isrTimerTick, TIMER_INTERVAL_US);
  Serial.print("Setup complete!\n");
}

void setRelayOn(void)
{
  digitalWrite(RELAY, RELAY_ON);
}

void setRelayOff(void)
{
  digitalWrite(RELAY, RELAY_OFF);
}

void setLEDOn(uint32_t led)
{
  digitalWrite(led, LED_ON);
}

void setLEDOff(uint32_t led)
{
  digitalWrite(led, LED_OFF);
}

void clearAllLEDs(void)
{
  setLEDOff(LED_GREEN);
  setLEDOff(LED_YELLOW);
  setLEDOff(LED_RED);
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
  gCtx.bGoButton = readButton(BUTTON_GO);

  if (gCtx.bGoButton == gCtx.bGoButtonDelay)
  {
    // button state stable and debounced
    gCtx.bGoCondition = !gCtx.bGoButton;
    gCtx.bStopCondition = gCtx.bGoButton;
    if (gCtx.bGoButton != gCtx.bButtonPrevious)
    {
      // change in button state
      if (gCtx.bGoButton) /* 0->1 */
      {
        eventHandlerGo(&stateTable[stateTable[gCtx.state].goEvent]);
      }
      else /* !gCtx.bGoButton 1->0 */
      {
        eventHandlerStop(&stateTable[stateTable[gCtx.state].stopEvent]);
      }
      // store off value
      gCtx.bButtonPrevious = gCtx.bGoButton;
    }
  }

  if (gCtx.state == stYellow)
  {
    gCtx.yellowCount++;
    if (gCtx.yellowCount == YELLOW_TIMEOUT_COUNT)
    {
      gCtx.yellowCount = 0;
      gCtx.bYellowTimeout = true;
      eventHandlerTimeout(&stateTable[stateTable[gCtx.state].timeoutEvent]);
    }
  }
}

void eventHandlerGo(stateTableEntry_t *pStateTableEntry)
{
  Serial.print("Event: goEvent, state:"); Serial.print(gCtx.state); Serial.print("\n");
  clearAllLEDs();
  // change state (if needed)
  gCtx.state = pStateTableEntry->goEvent;
  // set light based on state
  setLEDOn(pStateTableEntry->light);
  setRelayOn();
}

void eventHandlerTimeout(stateTableEntry_t *pStateTableEntry)
{
  Serial.print("Event: TimeoutEvent, state:"); Serial.print(gCtx.state); Serial.print("\n");
  clearAllLEDs();
  // change state (if needed)
  gCtx.state = pStateTableEntry->timeoutEvent;
  // set light based on state
  setLEDOn(pStateTableEntry->light);
}

void eventHandlerStop(stateTableEntry_t *pStateTableEntry)
{
  Serial.print("Event: stopEvent, state:"); Serial.print(gCtx.state); Serial.print("\n");
  clearAllLEDs();
  // change state (if needed)
  gCtx.state = pStateTableEntry->stopEvent;
  // set light based on state
  setLEDOn(pStateTableEntry->light);
  setRelayOff();
}

void loop()
{
  // nothing in main loop
}
