
/*
 * This program allows us to test our program on a single Servo.
 * This way, we can make changes on the setAngle function or see
 * if a Servo works.
 * 
 * The schematics are provided in this directory.
 * 
 */

int servo = 2; // The pin of the Servo

int period = 20000; // The period (in microseconds) between each Servo's impulsion

int transitionTime = 4; // The time between each Servo's rotation

void setup() {

  /*
   * In the setup, we simply initialize the Servo as an OUTPUT and 
   * turn if off.
   * 
   */
  
  pinMode(servo, OUTPUT); 
  
  digitalWrite(servo, LOW); 
  
}

void loop() {

  /*
   * This loop turns the Servo from 0° to 180°, and then
   * from 180° to 0°.
   * 
   * It was a mean for us to test if the Servo can rotate 
   * back and forth to 180°.
   * The reason we do it 1° at a time is that it seems to
   * be more fluid that way.
   * 
   */
  
  for (int angle = 0; angle <= 180; angle++) { 
    
    setAngle(angle, servo);
    
    delay(transitionTime);
    
  }
  
  for (int angle = 0; angle <= 180; angle++) { 
    
    setAngle((180 - angle), servo); 
    
    delay(transitionTime);
    
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
