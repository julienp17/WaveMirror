/* 
 * This is the main Arduino program of the project. 
 * 
 * After receiving the grayscale values of a row from the Raspberry Pi by I2C,
 * we begin to turn each Servos at an angle based on these values.
 *  
 * Since we need 48 Servos and each Arduino controls 8 of them, we need 
 * 6 Arduino in total. All Arduinos must use this program, but make sure 
 * to change the SLAVE_ADDRESS.
 * 
 * The Serial port must be used for debugging and not monitoring, otherwise it
 * will take too much time and slow down the program. 
 *
 * You can find the schematics in this directory.
 * 
 */

#include <Wire.h>
#include <Servo.h>

#define SLAVE_ADDRESS 0x03 // The address of the Arduino
// It goes from 0x03 to 0x077, so this is the first Arduino's code

const int NB_SERVOS = 8; // The number of Servos per Arduino

/**
 * The following is very appaling and repeats through the program,
 * unfortunately I haven't found any workaround it. Please contact me
 * if you find a solution !
 */
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;

int positions[NB_SERVOS]; // Table storing the positions of the Servos
int received = 0 ; // Counts the number of bytes received from the Raspberry Pi

void setup() {

  // Initialize each servo with its pin number
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);
  servo7.attach(8);
  servo8.attach(9);

  //Serial.begin(9600);
  //Serial.println("Arduino activated");
  
  Wire.begin(SLAVE_ADDRESS); // Begin the I2C communication as a 'slave' device
  Wire.onReceive(receiveData); // Define function called when we receive data
  
}

void loop() { 
  delay(100); // Check if we received something every 100 ms
}


void receiveData(int byteCount) { // Called everytime we receive data from the Rpi

  /**  
   *  The grayscale value received goes from 0 to 255, we map it to an 
   *  angle, which goes from 0 to 180. 
   *  
   *  It is better to store the values then move all the servos, rather 
   *  than moving the correct servo immediately after receiving the value,
   *  because otherwise the Arduino will be busy moving the servo while the 
   *  Raspberry Pi send it new values.
   */

  while(Wire.available()) {

    int color = Wire.read(); // Read the grayscale value from I2C communication

    //Serial.print("Color received = ");

    //Serial.print(color);

    int angle = map(color, 0, 255, 180, 0); // Map it to an angle

    //Serial.print(", angle converted = ");

    //Serial.println(angle);

    positions[received] = angle; // Store it

    received++; // Add +1 to the number of values we have received
    
  }

  /*
   * When we have received as much vales as we have Servos, we begin
   * to turn them.
   */

  if (received == NB_SERVOS){

    //Serial.println();

    //Serial.println("Beginning servo rotation...");

    /*
     * for (int i = 0 ; i < 8 ; i++){
     *   Serial.print("Servo n°");
     *   Serial.print(i+1);
     *   Serial.print(" : ");
     *   Serial.println(positions[i]);
     * }
     */
    
    // Move each servo to the stored angle
    servo1.write(positions[0]);
    servo2.write(positions[1]);
    servo3.write(positions[2]);
    servo4.write(positions[3]);
    servo5.write(positions[4]);
    servo6.write(positions[5]);
    servo7.write(positions[6]);
    servo8.write(positions[7]);
    delay(15);

    // Begin a new loop with new values
    received = 0;

    //Serial.println();
    //Serial.println("New values : ");
  }
}    
