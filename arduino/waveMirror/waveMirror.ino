#include <Wire.h>

/* 
 * You can find the schematics of this project at this link : //TODO
 *  
 * The Arduino receive the grayscale values of a row from the Raspberry Pi,  
 * and then controls 10 servos to adjust their position based of these values.
 *
 * This program is the code of the first Arduino. Since we need 120 servos and each Arduino
 * controls 10 Servos, we need 12 Arduino in total. You can find the codes of the other
 * Arduino's at : https://github.com/julienp17/WaveMirror/tree/master/arduino/waveMirror
 * They're the same programm, only the SLAVE_ADDRESS changes.
 * 
 * Throughout this code, the Raspberry Pi, acting as 'Master' in the I2C communication 
 * between itself and the Arduino, will be refered to as RPi. 
 * You will notice a lot of newlines and comments on this code, intended to help 
 * readability and comprehension for beginners.
 * 
 */

#define SLAVE_ADDRESS 0x04 // The slave address of the Arduino
// It goes from 0x03 to 0x077, so this is the first Arduino's code

const int SERVOS = 10; // The number of Servos per Arduino

int positions[SERVOS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // A table containing the current positions of the Servos

int newPositions[SERVOS]; // A table containing the new positions of the Servos

int received; // This variable counts the number of bytes byte received

int period = 20000; // The period (in microseconds) between each Servo's impulsion

int transitionTime = 4; // The time between each Servo's rotation

void setup() {

  /**
   * In the setup, we initialize each Servo as an OUTPUT, turn them off, and 
   * begin the I2C communication as a 'slave' device.
   * 
   * The pins of the Servos range from 2 to 12. This is because the first two pins
   * of the Arduino (TX and RX) are used for Serial communication.
   * 
   */

  for (int pinServo = 2; pinServo == 12; pinServo++){ 
    
    pinMode(pinServo, OUTPUT); 
    
    digitalWrite(pinServo, LOW); 
    
  }
  
  Serial.begin(9600); 
  
  Serial.println("Arduino activated.");
  
  Wire.begin(SLAVE_ADDRESS); // Begin the I2C communication as a 'slave' device
  
  Wire.onReceive(receiveData); // The function receiveData will be called everytime the RPi send a byte
  
}

void loop() { // This loop checks if a byte has been sent by the RPi every 100 ms
  
  delay(100); 
  
}


void receiveData(int byteCount) { 

  while(Wire.available()) {

    int color = Wire.read();

    Serial.print("Color received = ");

    Serial.print(color);

    int angle = map(color, 0, 255, 0, 180);

    Serial.print(", angle converted = ");

    Serial.println(angle);

    newPositions[received] = angle;

    received++;
    
  }

  if (received == SERVOS){

    Serial.println();

    Serial.println("Beginning servo rotation...");
    
    for (int servo = 0; servo < SERVOS; servo++){

      Serial.print("Servo n°");

      Serial.print(servo + 1);
      
      int prevAngle = positions[servo];

      Serial.print(" : current angle = ");

      Serial.print(prevAngle);
      
      int angle = newPositions[servo];

      Serial.print(", new angle = ");

      Serial.println(angle);

      int difference = abs(angle - prevAngle);
      
      for (int i = 0; i < difference; i++){
        
        if (angle > prevAngle){
          
          setAngle(i, (servo + 2) );
          
        } else {
          
          setAngle((difference - i), (servo + 2));
          
        }
        
        delay(transitionTime);
        
      }

      positions[servo] = angle;
      
    }

    received = 0;

    Serial.println("\nNew values :");
    
  }
  
}
   


void setAngle(int angle, int servo) {

  /**
   * This function sets a servo to an angle.
   * It allows us to create a sort of PWM signal even on non-PWM pins
   * by changing the duty cycle based on the angle.
   * 
   * @param angle
   *          The angle you want the Servo to turn to.
   * @param servo
   *          The Servo you want to turn.
   * 
   */

  int dutyCycle = map(angle, 0, 180, 545, 2500); // We get the correct duty cycle based of the angle. 
  // The default toLow and toHigh are 545 and 2500

  digitalWrite(servo, LOW); // Turn the Servo off

  digitalWrite(servo, HIGH); // Turn the Servo on

  delayMicroseconds(dutyCycle); // For the right time

  digitalWrite(servo, LOW); // Stop the impulsion

  delayMicroseconds(period - dutyCycle); // Wait for the rest of the period

}
