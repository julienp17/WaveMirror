# -*-coding:Utf-8 -*

"""This script executes our main program and shows the results of the
recorded image, taken from the Picamera.

It works a lot like the main program, which you can find at :
https://github.com/julienp17/WaveMirror/blob/master/raspberryPi/waveMirror/waveMirror.py
The difference is that we display the image along with the grid and grayscale
values, and don't send these value to Arduinos.

You can find a version of this script where the picture is not taken from
the PiCamera, but a picture of your choice at :
https://github.com/julienp17/WaveMirror/blob/master/raspberryPi/examples/camera/camera.py

"""

import psutil
import picamera
from PIL import Image, ImageDraw, ImageFont
from PIL.Image import *
from io import BytesIO
from time import sleep

# Create PiCamera and stream objects
camera = picamera.PiCamera()
stream = BytesIO()

# The larger the resolution, the clearer the image
# This also means bigger procession time
camera.resolution = (800, 600)
(l,h) = camera.resolution

divL = 12 # The output width
divH = 10 # The output height

# We calculate the width and height of each square in the grid
# The int type may left some pixels not in squares, but we can't have
# float pixel values
tailleH = int(h/divH)
tailleL = int(l/divL)

# Initialize Image.Draw to be able to draw later and a choose a font
draw = ImageDraw.Draw(image)
fnt = ImageFont.truetype('Pillow/Tests/fonts/FreeMono.ttf', 20)

# Let enough time for the camera to warmup
sleep(2)

# Capture the image in a stream
stream.seek(0)
camera.capture(stream, format="jpeg")

# Open the image, and convert it to black & white
image = open(stream).convert('L')

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

		# Draw the square on the image
		draw.rectangle(((pixLDepart, pixHDepart), (pixLFinal, pixHFinal)), outline="red")

		# Based on the grayscale value, we will write it either black or
		# white to make it visible
        if moyValPix > 165 :
            text_color = "black"
        else:
            text_color = "white"

		# At last, we write the grayscale value in the middle of the square
		draw.text(((pixLDepart+pixLFinal)/2, (pixHDepart+pixHFinal)/2), str(moyValPix), fill=text_color, font=fnt)

# When each square has been drawn and each greyscale value have been
# written in them, we show the image to the user
image.show() # The image is displayed by ImageMagick
