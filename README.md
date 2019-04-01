# WaveMirror

This repository is for an highschool project in Lycée George Brassens (St-Denis, Réunion, a french overseas department located in the Indian Ocean). It is based on [Daniel Rozin's Weave Mirror](https://smoothware.com/danny/weavemirror.html) with a 12x10 grid of servo-motors. This project help the students grow with interesting software and technologies such as Arduino, Raspberry Pi, SolidWorks or Scilab. It also uses a 3D Printer for moving parts that will be controlled by Servos.

A photo taken by a PiCamera is treated by a Raspberry Pi, which send the average grayscale values of the picture in 120 squares of pixels (12x10) to 10 Arduino via I2C communication. Each Arduino treats a row, converting these values in degrees (0-255 grayscale to 0-180 degrees) to control 12 servo-motors. The servo-motors rotate 3D printed white-to-black cylinders, which then displays the picture back to the user, making it act like a mirror. 

Material used :
- 1x [Raspberry Pi Model 3B+](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)
- 1x [PiCamera](https://www.amazon.com/Raspberry-Pi-Camera-Module-Megapixel/dp/B01ER2SKFS)
- 10x [Arduino UNO](https://store.arduino.cc/arduino-uno-rev3)
- 120x [HS-55 Servo-motors](https://www.servocity.com/hitec-hs-55-servo)
- 120x Semi-cylinders contrasted from white to black (3D Printed)

The cylinders were designed through SolidWorks by a student of the group project. 

We originally intended to use [Sparkfun PWM Shields](https://www.sparkfun.com/products/10615) to connect the Servos to the Arduinos. Unfortunately, we dropped this idea because it took too much of our time without working, and we learned that they don't actually work with I2C. 
If you want to make this project, we recommend trying it with the [Adafruit PWM Shield](https://www.adafruit.com/product/1411), or the [Arduino Mega](https://store.arduino.cc/arduino-mega-2560-rev3) to use less Arduinos and have more pins for the Servos.

The 4 students making this project have each been assigned to work on a different part :
- Scilab modelisation & simulation (RALAMBOARIVONY Teddy)
- Solidworks modelisation & 3D printing (GRONDIN Guillaume)
- Arduino connections & servos (FERRERE Guillyann)
- Raspberry Pi & Arduino code (PAUSE Julien) <-- Author of this repository

Since the author of this repository is responsible for the Raspberry Pi part, you'll find more ressources in that directory. However, don't hesitate to ask if you have any questions about other parts. 

Feel free to contact me about this project at : julien.pause17@gmail.com
