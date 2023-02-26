#define swPin 2
#define relayPin 3
#define ledPin 13

#define pdGndPin A2
#define pdPwrPin A1
#define pdSensePin A0

// TCNTn = 65535 – (16x10^6xTime in sec / Prescaler Value)
// 65535 − (((16 × (10^6)) × 4) / 1024) = 3035
float value = 3035;                   //Preload timer value (3035 for 4 seconds)

bool timerEvent = false;
bool ledState = false;

constexpr uint16_t ANALOG_TRIP_VALUE = 0x300;
constexpr uint16_t TRIP_COUNT_LIMIT = 8; // 8 * 4s = 32s
constexpr uint16_t LIGHT_ON_LIMIT = 1800; // 2 × hour = 7200 s, 7200s / 4s interval = 1800

void setup()
{
    Serial.begin(115200);

    pinMode(swPin, INPUT_PULLUP);
    pinMode(relayPin, OUTPUT);
    pinMode(ledPin, OUTPUT);

    pinMode(pdGndPin, OUTPUT);
    pinMode(pdPwrPin, OUTPUT);
    pinMode(pdSensePin, INPUT);

    digitalWrite(pdPwrPin, HIGH);
    digitalWrite(pdGndPin, LOW);

    noInterrupts();                       // disable all interrupts

    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = value;                        // preload timer
    TCCR1B |= (1 << CS10)|(1 << CS12);    // 1024 prescaler
    TIMSK1 |= (1 << TOIE1);               // enable timer overflow interrupt ISR

    interrupts();                         // enable all interrupts
}

// interrupt service routine for overflow
ISR(TIMER1_OVF_vect)
{
    TCNT1 = value;  // preload timer
    timerEvent = true;
}

typedef enum state_e
{
    stateIdle               = 0x0,
    stateDarkDetect         = 0x1,
    stateNightLiteOn        = 0x2,
    stateNightLiteUnarmed   = 0x3,
    stateLightDetect        = 0x4,
} state_e;

state_e state = stateIdle;
uint16_t timerCount = 0;

state_e darkDetection(uint16_t value);
state_e darkDetection(uint16_t value)
{
    state_e ns;
    if (value > ANALOG_TRIP_VALUE)
    {
        timerCount++;
        ns = stateDarkDetect;
    }
    else
    {
        timerCount = 0;
        ns = stateIdle;
    }
    return ns;
}

state_e lightDetection(uint16_t value);
state_e lightDetection(uint16_t value)
{
    state_e ns;
    if (value < ANALOG_TRIP_VALUE)
    {        
        timerCount++;
        ns = stateLightDetect;
    }
    else
    {
        timerCount = 0;
        ns = stateNightLiteUnarmed;
    }
    return ns;
}

void enableNightLight(bool on);
void enableNightLight(bool on)
{
    digitalWrite(relayPin, on);
}

void loop()
{
    if(timerEvent == true)
    {
        timerEvent = false;
        digitalWrite(ledPin, ledState);
        ledState = !ledState;
        uint16_t sensorValue = analogRead(pdSensePin);
        Serial.println(sensorValue, HEX);
        Serial.println(state, HEX);
        switch (state)
        {
            case stateIdle:
                // daylight, waiting for nightfall
                enableNightLight(false);
                state = darkDetection(sensorValue);
                break;
            case stateDarkDetect:
                // twilight, waiting for consistent dark detection
                enableNightLight(false);
                state = darkDetection(sensorValue);
                if (state == stateDarkDetect && timerCount >= TRIP_COUNT_LIMIT)
                {
                    // consistent dark detection -> turn on night light
                    timerCount = 0;
                    state = stateNightLiteOn;
                }
                break;
            case stateNightLiteOn:
                // night, light on for set time
                enableNightLight(true);
                timerCount++;
                if (timerCount >= LIGHT_ON_LIMIT)
                {
                    timerCount = 0;
                    state = stateNightLiteUnarmed;
                }
                break;
            case stateNightLiteUnarmed:
                // nightime, waiting for dawn
                enableNightLight(false);
                state = lightDetection(sensorValue);
                break;
            case stateLightDetect:
                // dawn, waiting for consistent light detection
                enableNightLight(false);
                state = lightDetection(sensorValue);
                if (state == stateLightDetect && timerCount >= TRIP_COUNT_LIMIT)
                {
                    // consistent dark detection -> turn on night light
                    timerCount = 0;
                    state = stateIdle;
                }
                break;
        }
        if (!digitalRead(swPin))
        {
          enableNightLight(true);
        }
    }
}
