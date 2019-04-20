#include <Wire.h>

/* 
 * This is the main Arduino program of the project. 
 * 
 * After receiving the grayscale values of a row from the Raspberry Pi,
 * we begin to turn each Servos at an angle based of these values.
 *  
 * Since we need 120 Servos and each Arduino controls 10 of them, we need 
 * 12 Arduino in total. You can all pass them this program, but make sure 
 * to change the SLAVE_ADDRESS
 *
 * 
 * You can find the schematics in this directory.
 * 
 */

#define SLAVE_ADDRESS 0x03 // The slave address of the Arduino
// It goes from 0x03 to 0x077, so this is the first Arduino's code

const int SERVOS = 10; // The number of Servos per Arduino

int positions[SERVOS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // A table that stocks the current positions of the Servos
// At the beginning, we assume each Servos has been initialsed to 0 degrees.

int newPositions[SERVOS]; // A table that will stock the new positions of the Servos

int received; // This variable counts the number of bytes received from the Raspberry Pi

int period = 20000; // The period (in microseconds) between each Servo's impulsion

int transitionTime = 4; // The time between each Servo's rotation

void setup() {

  /**
   * In the setup, we initialize each Servo as an OUTPUT, turn them off, and 
   * begin the I2C communication as a 'slave' device.
   * 
   * The pins of the Arduino range from 2 to 13. This is because the first two 
   * pins (TX and RX) are used for Serial communication.
   * We use 10 Servos so we conenct them from pin 2 to pin 12.
   * 
   */

  for (int pinServo = 2; pinServo == 12; pinServo++){ 
    
    pinMode(pinServo, OUTPUT); // Initialize each Servo as an OUTPUT
    
    digitalWrite(pinServo, LOW); // Turn them off
    
  }
  
  //Serial.begin(9600); 
  
  //Serial.println("Arduino activated.");
  
  Wire.begin(SLAVE_ADDRESS); // Begin the I2C communication as a 'slave' device
  
  Wire.onReceive(receiveData); // The function receiveData will be called everytime the RPi send a byte
  
}

void loop() { // This loop checks if a byte has been sent by the RPi every 100 ms
  
  delay(100); 
  
}


void receiveData(int byteCount) {

  /* 
   *  This function is called everytime the RPi sends a byte.
   *  
   *  First, we map the grayscale value received (from 0 to 255) 
   *  to an angle (from 0 to 180), then we stock it in a table
   *  containing the requested new positions.
   *  
   *  It is a better solution to stock the new positions and then 
   *  move all Servos at once, rather than getting a new value and 
   *  immediately moving the correct Servo. 
   *  The reason is that, in the second case, while the Arduino is 
   *  busy moving the Servo, the Raspberry Pi still send it new values. 
   *  Since the Arduino is busy, it won't receive these new values, 
   *  leading the script to crash on the Raspberry Pi's side.
   *  
   *  That's why we count how much values we receive : to determine
   *  when should we move the Servos. In that case, the Raspberry Pi
   *  will be sending new values to other Arduinos while we're busy.
   *  
   */

  while(Wire.available()) {

    int color = Wire.read(); // Read the grayscale value from I2C communication

    //Serial.print("Color received = ");

    //Serial.println(color);

    int angle = map(color, 0, 255, 0, 180); // Map it to an angle

    //Serial.print(", angle converted = ");

    //Serial.println(angle);

    newPositions[received] = angle; // Stock it in the table containing the new positions

    received++; // Add +1 to the number of values we have received
    
  }

  /*
   * When we have received as much vales as we have Servos, we begin
   * to turn them.
   */

  if (received == SERVOS){

    //Serial.println();

    //Serial.println("Beginning servo rotation...");
    
    for (int servo = 0; servo < SERVOS; servo++){ // For each servo

      //Serial.print("Servo n°");

      //Serial.print(servo + 1);
      
      int prevAngle = positions[servo]; // We get its current position

      //Serial.print(" : current angle = ");

      //Serial.print(prevAngle);
      
      int angle = newPositions[servo]; // We get its requested new position

      //Serial.print(", new angle = ");

      //Serial.println(angle);

      int difference = abs(angle - prevAngle); // We calculate the difference between them

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
      
      for (int i = 0; i < difference; i++){
        
        if (angle > prevAngle){
          
          setAngle(i, (servo + 2) ); // We have to add + 2 to the servo to get its pin. Remember, the first Servo's pin is 2.
          
        } else {
          
          setAngle((difference - i), (servo + 2));
          
        }
        
        delay(transitionTime);
        
      }

      positions[servo] = angle; // Update the current position of the Servo to the new position
      
    }

    received = 0; // And begin a new loop 

    //Serial.println("\nNew values :");
    
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
