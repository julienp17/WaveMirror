/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
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
