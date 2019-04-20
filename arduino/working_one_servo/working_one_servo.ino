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

Servo servo_deux;  
Servo servo_trois;
Servo servo_quatre;
Servo servo_cinq;
Servo servo_six;
Servo servo_sept;
Servo servo_huit;  
Servo servo_neuf;

int received = 0;

void setup() {
  servo_deux.attach(2);  
  servo_trois.attach(3);
  servo_quatre.attach(4);  
  servo_cinq.attach(5);
  servo_six.attach(6);  
  servo_sept.attach(7);
  servo_huit.attach(8);  
  servo_neuf.attach(9);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
}

void loop() {
  delay(100);                      // waits for the servo to get there
}

void receiveData(int byteCount) {
  while(Wire.available()) {
    int color = Wire.read();
    int angle = map(color, 0, 255, 180, 0);
    received++;
  }
    if (pouf == 0){
      servo_deux.write(angle);
      pouf++;
  } else {
      servo_trois.write(angle);
      pouf--;
  }
  }
}
