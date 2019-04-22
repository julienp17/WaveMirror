/*
 * This program allows us to test the I2C feature.
 * 
 * You can use it with the Raspberry Pi's python script located 
 * at : TODO
 * The Raspberry Pi acts as the 'Master' and the Arduino as a
 * 'slave' device.
 * 
 * The schematics are provided in this directory.
 * 
 */

#include <Wire.h>

#define SLAVE_ADDRESS 0x03 // The slave address of the Arduino
// It goes from 0x03 to 0x077
// Make sure they are the same in this code and the Raspberry Pi's python script

int color; // The byte the Raspberry Pi will send to us

int number; // The number of bytes the Raspberry Pi has sent

void setup() {
  
   // Initialiaze the Serial Port
   Serial.begin(9600);
   Serial.println("Arduino activated.");
   
   // Initialize the I2C communication, making the Arduino the 'slave' device
   Wire.begin(SLAVE_ADDRESS);
   
   // Define the function called when the Master sends a byte
   Wire.onReceive(receiveData);
 
}
 
void loop() { // This loop checks if a byte has been sent by the Raspberry Pi every 100 ms
  
  delay(100);
  
}
 
void receiveData(int byteCount){ // This function is called everytime the Raspberry Pi sends a byte.
 
   while(Wire.available()) { // While a byte is waiting to be read

    /*
     * Since each Arduino is supposed to control 10 Servos in the actual program,
     * we separate each block when the number of bytes the Raspberry Pi has sent
     * is superior or equal to 10.
     * 
     */
    if (number >= 10){ 
      
      number = 0;
      
      Serial.println("\nNew values : ");
      
    }
    
    number++; // Make an index for each byte
    
    color = Wire.read(); // Read the byte sent by the Raspberry Pi

    /**
     * The following code does NOT have bad syntax.
     * 
     * Writing it with string concatenation will cause the Serial print to fail, 
     * and only display parts of the string instead.
     * 
     * The following does NOT work :
     *      Serial.print("Number " + number + " received = " + color);
     * 
     */
    
    Serial.print("Number ");
    
    Serial.print(number);
    
    Serial.print(" received : " );
    
    Serial.println(color);
    
   }
 
}
