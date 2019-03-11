# -*-coding:Utf-8 -*

"""This script is the main program of our project.

The Python version is 2.7.13
To upgrade you must install the Pillow library instead of PIL.

The goal is to capture the image of the PiCamera, convert it to black & white,
cut the image in 12*10 squares of pixels, get the grayscale values of each of 
those squares, and then send these values to each Arduino via I2C.

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

output_width = 12 # Number of Arduinos
output_height = 10 # Number of Servos an Arduino controls

# The larger the resolution, the clearer the image
# This also means bigger procession time
camera.resolution = (800, 600) 
(width, height) = camera.resolution

# We calculate the width and height of each square in the grid
# The int type may left some pixels not in squares, but we can't have
# float pixel values
tailleL = int(width / output_width)
tailleH = int(height / output_height)
nb_pixels = tailleH * tailleL

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

    # For each square, we get its first and last height pixel
    for hauteur in range(output_height): 
        pixHDepart = tailleH * hauteur

        # Same thing for its first and last width pixel
        for longueur in range(output_width):
            pixLDepart = tailleL * longueur

            sum_gray = 0

            # We iterate through every pixel in the square, get its grayscale
			# value, and add it to the sum of gray in the square
            for y in range(tailleH):
                for x in range(tailleL):
                    coordX = x + (pixLDepart)
                    coordY = y + (pixHDepart)
                    current_pixel_value = Image.getpixel(image, (coordX, coordY))
                    sum_gray += current_pixel_value
                    a += 1

            # We divide the sum of gray in the square by the number
			# of pixels the square have, to get its average greyscale value
            average_gray = int(sum_gray / nb_pixels) 

            # Each Arduino treats a row, so we send 12 values to each of them.
            # That means if we have sent 12 values, we change Arduinos.
            if (case%12)+1 == 1 :
                arduino += 1
            case +=1

            # Finally, we send the value to the correct Arduino
            bus.write_byte(arduino, average_gray)

            # Let the program rest a bit
            sleep(0.001)
