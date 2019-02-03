# -*-coding:Utf-8 -*

"""This script is the main program of our project.

It was programmed for use with python2.7
Python3 doesn't work because of the PIL library.

The goal is to capture the image of the PiCamera, convert it to black & white,
cut the image in 12*10 squares of pixels, get the grayscale values of each of 
those squares, and then send these grayscale values to each Arduino via I2C.

You can find the Arduino's code at :
https://github.com/julienp17/WaveMirror/blob/master/arduino/waveMirror/waveMirror.ino

You can find the schematics in this directory.

"""

import smbus
import picamera
from PIL import Image
from PIL.Image import *
from io import BytesIO
from time import sleep

# Create SMBus, PiCamera, and stream objects
bus = smbus.SMBus(1)
camera = picamera.PiCamera()
stream = BytesIO()

divL = 12 # The output width => Number of Arduinos
divH = 10 # The output height => Number of Servos an Arduino controls

# The larger the resolution, the clearer the image
# This also means bigger procession time
camera.resolution = (800, 600) 
(l,h) = camera.resolution

# Uncomment below this if you want a live preview of what the camera captures
# It only works if the Raspberry Pi's is connected to a monitor, not VNC
### camera.start_preview()

# Let enough time for the camera to warmup
sleep(2)

while True:

    case = 0 # The current square

    # The Arduino address, going from 0x03 to 0x77
    arduino = 2 # Same as writing => arduino = 0x02
    
    # Capture the image in a stream
    stream.seek(0)
    camera.capture(stream, format="jpeg")

    # Open the image, and convert it to black & white
    image = open(stream).convert('L')

    # We calculate the width and height of each square in the grid
	# The int type may left some pixels not in squares, but we can't have
	# float pixel values
    tailleH = int(h/divH)
    tailleL = int(l/divL)

    # For each square, we get its first and last height pixel
    for hauteur in range(divH): 
        pixHDepart = tailleH * hauteur
        pixHFinal = tailleH * (hauteur + 1)

        # Same thing for its first and last width pixel
        for longueur in range(divL):
            pixLDepart = tailleL * longueur
            pixLFinal = tailleL * (longueur + 1)

            a = 0
            sommeValPix = 0

            # We iterate through every pixel in the square, get its grayscale
			# value, and add it to the sum of gray in the square
            for y in range(tailleH):
                for x in range(tailleL):
                    coordX = x + (pixLDepart)
                    coordY = y + (pixHDepart)
                    valPixCourant = Image.getpixel(image, (coordX, coordY))
                    sommeValPix += valPixCourant
                    a += 1

            # We divide the sum of gray in the square by the number
			# of pixels the square have, to get its average greyscale value
            moyValPix = int(sommeValPix / a) 

            # Each Arduino treats a row, so we send 10 values to each of them.
            # That means if we have sent 10 values, we change Arduinos.
            if (case%10)+1 == 1 :
                arduino += 1
            case +=1

            # Finally, we send the value to the correct Arduino
            bus.write_byte(arduino, moyValPix)

            # Let the program rest a bit
            sleep(0.001)
