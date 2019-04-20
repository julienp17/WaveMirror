/**
 * This program is used to test a servo.
 * 
 * After receiving values from I2C, that we assume is grayscale values 
 * from the Raspberry Pi, we map it to an angle and turn the Servo to
 * that angle.
 * 
*/

#include <Servo.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x03

Servo myservo;

void setup() {
  myservo.attach(2);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
}

void loop() {
  delay(100); // waits for the servo to get there
}

void receiveData(int byteCount) {
  while(Wire.available()) {
    int color = Wire.read();
    int angle = map(color, 0, 255, 180, 0);
    myservo.write(angle);
  }
}