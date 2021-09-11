//
// Using a Laser Pointer and a 8x8 Matrix LED
// as Two-dimensional Input device
//   Developed Eiji Hayashi  
//   2010/03/26 Version 1.0
//
// *** What's this? ***
// This is a sample code which shows how we can use 
// a 8x8 matrix LED as a light sensor array, and
// how we can detect position of a LED pointed by
// a laser pointer.
// 
// *** Wiring ***
// This code assumes:
//   D2 to D9 are connected to cathodes 
//   A0 to A7 are connected to anodes
//   D11 and D12 are connected to A6 and A7 respectively
// Please refer to circuit diagrams for more details.
//
// *** How it works ***
// When you turn on a circuit, all LEDs turn on one-by-one.
// After that LEDs pointed by a laser pointer turn on.
//

#include <util/delay.h>

#define DEBUG 1

constexpr int MAX_ROWS = 8;
constexpr int MAX_COLS = 8;

// A technique to make analogRead faster
// See http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1208715493/11
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

int screen[8] = {0,0,0,0,0,0,0,0};  // bits displayed on the LED matrix
int thresh[8] = {0,0,0,0,0,0,0,0};  // threshold values used in CheckColumn()
                                    // the thresholds are adjusted in
                                    // adjustThreshCol()

static int ledCntr;
static int ledState;

// Initial setup
void setup(){
  int rows[8] = { 2, 3, 4, 5, 6, 7, 8, 9};
  int cols[8] = { 14, 15, 16, 17, 18, 19, 11, 12 };

#if DEBUG
  Serial.begin(115200);
#endif
  DDRC = B11111111;
  DDRD = B11111111;
  PORTD = B11111111;

  // Adjust prescaler to make analogReadFaster
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;

  // Adjust threshold for column detection
  while(1)adjustThreshCol();
  
  // Turn on LEDs one-by-one for sanity check
  for( int i=0; i<MAX_ROWS; i++ ){
    pinMode( rows[i], INPUT );
    pinMode( cols[i], OUTPUT );
  }
    
  for( int i=0; i<MAX_ROWS; i++ ){
    pinMode(rows[i], OUTPUT );
    digitalWrite( rows[i], LOW );
    for( int j=0; j<MAX_COLS; j++ ){
      digitalWrite( cols[j], HIGH );
      delay(50);
      digitalWrite( cols[j], LOW );
    }
    pinMode( rows[i], INPUT );
  }
}

// Main loop
// Detect a laser pointer and turn a pointed LED on
void loop()
{
  // detect a pointer
  // if no pointer is detected, 8 will be returned.
  int row = checkRow();  
  int col = checkColumn();

  // put 1 at the pointed location
  if( row != MAX_ROWS && col != MAX_COLS )
     screen[row] |= 1 << col;
  
#if DEBUG2
  Serial.print(row);
  Serial.print(",");
  Serial.println(col);
#endif

  // Show the content of screen
  DDRC |= B00111111;  // make column 0 to 5 port output
  DDRB |= B00011000;   // make column 6 and 7 output
  DDRD &= B00000011;  // make row 0 to 5 input
  DDRB &= B11111100;  // make row 6 and 7 input
  
  for( int i=0; i<5; i++ ){
    for( int row=0; row<MAX_ROWS; row++ ){
      
      if( row<6 ){
        DDRD |= 1 << (row+2);
      }
      else{
        DDRB |= 1 << (row-6);
      }
   
      PORTC = screen[row] & B00111111;
      PORTB = ( screen[row] & B11000000 ) >> 3;
      _delay_us( 300 );
  
      DDRD &= B00000011;
      DDRB &= B11111100;
    }
  }
}

// Check which column is pointed
int checkColumn(){
  int val[MAX_COLS];  // brightness

  // *** clear charges ***
  // make all anodes output and low
  DDRB = B00011000;
  PORTB = B00000000;
  DDRC = B11111111;
  PORTC = B00000000;

  // make all cathodes output and low;
  DDRD |= B11111100;
  DDRB |= B00000011;
  PORTD &= B00000011;
  PORTB &= B11111100;

  _delay_us(10);  // wait for a while to clear charges

  // make all anodes input to measure charges cause by light
  DDRB &= B11100111;
  DDRC = B00000000;
  
  _delay_us(200);  // wait for a while 
  
  // read analog values at all anodes
  for( int col=0; col<MAX_COLS; col++ ){
    val[col] = analogRead( col );
  }
  
  // calculate difference between current values and thresholds
  for( int col=0; col<MAX_COLS; col++ ){
    val[col] = val[col] - thresh[col];
  }
 
 
  // if the differences are bigger than 10,
  // the column is pointed by a laser pointer
  int signal = MAX_COLS; 
  for( int col=0; col<MAX_COLS; col++ ){
    if( val[col] > 10 ){
      signal = col;
      break;
    }
  }
  
#if DEBUG2
  for( int col=0; col<(MAX_COLS-1); col ++ ){
    Serial.print(val[col]);
    Serial.print(",");
  }
  Serial.println(val[MAX_COLS-1]);
#endif
  
  return( signal );
  
}

// Measure analog values at anodes to calculate threshold values.
// Using the threshold values mitigates effects of ambient light conditions
void adjustThreshCol()
{
  for( int cnt=0; cnt<100; cnt ++ ){  // measure the values 100 times and take average
    int val[8];

    // *** clear charges ***
    // make all anodes output and low
    DDRB = B00011000;
    PORTB = B00000000;
    DDRC = B11111111;
    PORTC = B00000000;
  
    // make all cathodes output and low;
    DDRD |= B11111100;
    DDRB |= B00000011;
    PORTD &= B00000011;
    PORTB &= B11111100;
  
    _delay_us(10);  // wait for a while to clear charges
  
    // make all anodes input to measure charges cause by light
    DDRB &= B11100111;
    DDRC = B00000000;

    _delay_us(200);
    int input = 0;
    for( int i=0; i<MAX_COLS; i++ ){
      val[i] = analogRead( i );
      thresh[i] += val[i];
    }
  }  
  
  // take average
  for( int i=0; i<MAX_COLS; i++ ){
    thresh[i] = thresh[i] / 100;
  }
      
#if DEBUG
  Serial.println( "Thresholds:" );
  for( int r=0; r<(MAX_COLS-1); r++ ){
    Serial.print( thresh[r] );
    Serial.print(",");
  }
  Serial.println( thresh[MAX_COLS-1] );
#endif  
}

// Check which row is pointed
int checkRow()
{
  int input = 0;
  
  // *** Apply reverse voltage, charge up the pin and led capacitance 
  // make all cathodes high
  DDRD |= B11111100;
  DDRB |= B00000011;
  PORTD |= B11111100;
  PORTB |= B00000011;
  
  // set all anodes low
  DDRC = B00111111;
  PORTC = B11000000;
  DDRB |= B00011000;
  PORTB &= B11100111;

  _delay_us(1000);  // wait for a while to charge
  
  // Isolate the pin connected to cathods
  DDRD &= B00000011;  // make N0-N5 INPUT
  DDRB &= B11111100;  // make N6 and N7 INPUT
  
  // turn off internal pull-up resistor
  PORTD &= B00000011; // make N0-N5 LOW
  PORTB &= B11111100; // make N6 and N7 LOW  

  // measure how long it takes for cathodes to become low
  int val[8] = {100,100,100,100,100,100,100,100};
  for( int cnt=0; cnt<50; cnt++ ){
    for( int r=0; r<MAX_ROWS; r++ ){
      if( (digitalRead( 2+r ) == LOW)&& (val[r] == 100) )
        val[r] = cnt;
    }
  }

  // if a pin becomes low quicker than 50, the pin is pointed
  int signal = MAX_ROWS;
  for( int i=0; i<MAX_ROWS; i++ ){
    if( val[i] < 49 ){
      signal = i;
      break;
    }
  }
    
#if DEBUG
  for( int r=0; r<(MAX_ROWS-1); r++ ){
    Serial.print( val[r] );
    Serial.print(",");
  }
  Serial.println( val[MAX_ROWS-1] );
  Serial.println( signal );
#endif
  
  return( signal );
}
