# WaveMirror

This repository is for an highschool project in Lycée George Brassens (St-Denis, Réunion, France). It is based on [Daniel Rozin's Weave Mirror](https://smoothware.com/danny/weavemirror.html) with a 12x10 grid of servo-motors.
This project help the students develop with interesting software and technologies such as Arduino, Raspberry PI, SolidWorks or Scilab. It also uses a 3D Printer for moving parts that will be controlled by Servos.

Material used :
	-   1x [Raspberry Pi Model 3B+](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)
	-   1x [PiCamera](https://www.amazon.com/Raspberry-Pi-Camera-Module-Megapixel/dp/B01ER2SKFS)
	-  10x [Arduino UNO](https://store.arduino.cc/arduino-uno-rev3)
	-  10x [Sparkfun PWM Shield](https://www.sparkfun.com/products/10615)
	- 120x [HS-55 Servo-motors](https://www.servocity.com/hitec-hs-55-servo)
	- 120x Semi-cylinders contrasted from white to black (3D Printed)
Everything was provided by the highschool, and the cylinders were designed through SolidWorks by a student of the group project.  

A photo taken by a PiCamera is treated by a Raspberry Pi, which send the average grayscales values of the picture in 120 portions of pixels (12x10) to 10 Arduino via I2C communication. Each Arduino treats a row, converting these values in degrees (0-255 grayscale to 0-180 degrees), and sending them to 12 servo-motors through a Sparkfun PWM Shield. The servo-motors rotate  white-to-black cylinders which then displays the picture back to the user, in the same style as a gray mirror. 

The 4 students making this project have each been assigned to work on a different part :
	- Raspberry Pi & I2C
	- Arduino & Servos
	- Solidworks modelisation and 3D printing
	- Scilab modelisation and simulation