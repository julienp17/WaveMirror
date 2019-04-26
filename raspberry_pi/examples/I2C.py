# -*-coding:Utf-8 -*

"""This script allows us to test the I2C communication on the Raspberry Pi.

You can use it with the Arduino's script located at : 
https://github.com/julienp17/WaveMirror/blob/master/arduino/examples/I2C/I2C.ino
The Raspberry Pi acts as the 'Master' and the Arduino as a 'slave' device.

We send one byte to the Arduino, and it should print it in the Serial monitor.

The schematics are provided in this directory.

"""

import smbus
from time import sleep

# Create object for SMBus class
# On older hardware, you might need to write SMBus(0) instead of SMBus(1)
bus = smbus.SMBus(1)

# The addresses go from 0x03 to 0x77, make sure they are the same in this 
# script and the Arduino code.
arduino = 0x03 # Writing this is the same as writing => arduino = 3

# Choose a byte to send to the Arduino
char = input("Send a character to the Arduino : "))
bus.write_byte(arduino, char)

# Sleep for 1 second to let the script run
sleep(1)
