// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

// 04-Feb-2018 mcarter adapted
#include <Wire.h>

const int ledPin = 13; // onboard LED
static_assert(LOW == 0, "Expecting LOW to be 0");

void setup() {
  Wire.begin(0x8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // turn it off
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    digitalWrite(ledPin, c);
  }
}
