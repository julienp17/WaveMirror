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

#define SLAVE_ADDRESS 0x03 // The slave address of the Arduino
// It goes from 0x03 to 0x077, so this is the first Arduino's code

int color; // The byte sent by the Rpi (between 0 and 255)

int angle; // The angle which the Servo will turn to, based on the color (between 0 and 180)

int prevAngle; // The angle which the Servo is currently at

int difference; // The difference between the current angle and the requested one

int positions[9]; // A table containing the current angle of all Servos

int servo = 1; // The pin of the Servos

int periode = 20000; 
int tempsTransition = 4;

void setup() {

  /**
   * In the setup, we initialize each Servo as an OUTPUT, turn them off, and 
   * begin the I2C communication as a 'slave' device.
   * 
   * The pins of the Servos range from 2 to 12. This is because the first two pins
   * of the Arduino (TX and RX) are used for Serial communication.
   * 
   */

  for (int servo = 2; servo == 12; servo++){ 
    
    pinMode(servo, OUTPUT); 
    
    digitalWrite(servo, LOW); 
    
  }
  
  Serial.begin(9600); 
  
  Serial.println("OK");
  
  Wire.begin(SLAVE_ADDRESS); 
  
  Wire.onReceive(receiveData); // The function receiveData will be called everytime the RPi send a byte
  
}

void loop() { // This loop checks if a byte has been sent by the RPi every 100 ms
  
  delay(100); 
  
}


void receiveData(int byteCount) { 
  
  /* 
   *  This function is called everytime the RPi sends a byte.
   *  
   *  First, we determine which Servo needs to turn. Based of 
   *  the grayscale value sent by the RPi, we map it to an angle,
   *  turn the Servo to this angle, and update it in the table
   *  that keeps all the Servos positions.
   *  
   */
  
  while(Wire.available()){ // While a byte is waiting to be read
    
    servo++; // We change Servos
    
    if (servo > 12){ // We return to the beginning if the pins are out of bounds
      
      servo = 2; // The pin 2 being the beginning
      
    }
    
    color = Wire.read(); // We read the byte that the RPi sent
    
    angle = map(color, 0, 255, 0, 180); // Convert it to an angle
    
    prevAngle = positions[servo - 2]; // We get the current angle of the Servo. Since the pin 2 corresponds to the
    // first Servo, and 0 is the index of this first Servo in the table, we need to substract 2 to get the correct index.

    positions[servo - 2] = angle; // We update the angle to the new one
    
    difference = abs(angle - prevAngle); // We get the difference between the current angle and the new one

    /**
     * If the new angle is bigger than the current one, we will increment the angle 1 by 1 until we get to that new angle. 
     * ex : from 106 to 180 => 106, 107, 108...
     * 
     * Else, we will decrement 1 by 1 to that new angle.
     * ex : from 180 to 106 => 180, 179, 178...
     * 
     * The reason we do it 1 by 1 instead of straigth away is because it seems more fluid operating that way.
     * 
     * In the case that the new angle is equal to the current one, we simply don't do anything.
     * 
     */

    if (angle > prevAngle){ 
      
      for (int x = 0; x <= difference; x++){ 
        
        setAngle(x, servo); 
        
        delay(tempsTransition); 
        
      }   
      
    } else if (angle < prevAngle) { 
      
      for (int x = 0; x <= difference; x++){ 
        
        setAngle((difference - x), servo); 
        
        delay(tempsTransition);
        
      }
      
    }
   
  } 
  
}

void setAngle(int angle, int servo) {

  /**
   * This function sets a servo to an angle.
   * It allows us to create a sort of PWM signal even on non-PWM pins.
   * 
   * @param angle
   *          The angle you want the Servo to turn to.
   * @param servo
   *          The Servo you want to turn.
   * 
   */

  int duration = map(angle, 0, 180, 545, 2500); // We get the correct duration based of the angle. 
  // The default toLow and toHigh are 545 and 2500

  digitalWrite(servo, LOW); // Turn the Servo off

  digitalWrite(servo, HIGH); // Turn the Servo on

  delayMicroseconds(duration); // For the right duration

  digitalWrite(servo, LOW); // Stop the impulsion

  delayMicroseconds(periode - duration); // Wait for the rest of the time

}
