
#include <util/delay.h>

constexpr int led_p = 2;
constexpr int aled_n = A0;

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define FASTADC 1
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led_p, OUTPUT);
  pinMode(aled_n, OUTPUT);
  #if FASTADC
  // set prescale to 16
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
  #endif
}

static int ledCntr;
static int ledState;

void loop() {
  // put your main code here, to run repeatedly:
  // Reverse bias the LEDs by making D0 and D1 HIGH, and A0 and A1 LOW.
  // Make D0 and D1 INPUT. Initially, both of them are HIGH because of current charged in the LEDs.
  // Then, as the current leaks, D0 and D1 becomes LOW after a certain period.
  // Turn on
  pinMode(aled_n, OUTPUT);
  digitalWrite(led_p, HIGH);
  digitalWrite(aled_n, LOW);
  delay(10);

  // Reverse
  digitalWrite(led_p, LOW);
  digitalWrite(aled_n, HIGH);
  _delay_us( 300 );
  // Make _n Input
  pinMode(aled_n, INPUT);
  ledState = analogRead(aled_n);
  ledCntr = 0;
  while(ledState > 0)
  {
    ledState = analogRead(aled_n);
    _delay_us( 1 );
    ledCntr++;
  }
  if (ledCntr < 10)
  {
    Serial.println("LASER Detected!"); 
    Serial.println(ledCntr);
    Serial.println(ledState);
  }
}
