# State Machines
Various implementations of state machines in C. These examples were developed in the Arduino environment targeting a Teensy 3.0. 

Examples were based off of descriptions provided in *Making Embedded Systems* by Elecia White.

All three examples are of a stoplight. A teensy 3.0 was connected to red, yellow, and green LEDs. A simple swtich was connected to simulate a car detection sensor.

Serial output was configured at 115200bps.

The examples use a TimerInterval instance as an ISR at 100ms.
## Pinout
Type | Pin
---- | ---
Green LED | 13
Yellow LED | 14
Red LED | 15
Switch | 16
## Event Cetric
State transitions handling in ISR.
## State Cetric
State transitions handling in main loop, events handled in ISR.
## Table Driven
State transition table used to decide next state and outputs.