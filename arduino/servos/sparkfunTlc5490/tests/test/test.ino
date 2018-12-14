#include <Wire.h>
#include "SparkFun_Tlc5940.h"
#include "tlc_servos.h"

#define SERVO_CHANNEL 0
#define SLAVE_ADDRESS 0x03
#define DELAY_TIME 20

int gray;
int angle;
int nombre = 0;
int numero = 0;

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  tlc_initServos();
  delay(3000);
}

void loop(gray) {
  tlc_setServo(SERVO_CHANNEL, 0);
  Tlc.update();
  delay(2000);
  gray = random(256);
  angle = map(gray, 0, 255, 0, 180);
  tlc_setServo(SERVO_CHANNEL, angle);
  Tlc.update();
  delay(2000);
}

void receiveData(int byteCount) {
  while(Wire.available()) {
    gray = Wire.read();
  }
}

void sendData() {
}
}
