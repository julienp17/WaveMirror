# -*-coding:Utf-8 -*

"""This script is an alternate program for the day of the presentation.

It displays in a loop 3 pictures of a smiley, one where it's smiling, one 
where it's neutral, and one where it's sad. The pictures are displayed with 
a grid on top of them, showcasing the grayscale value of each square.

This program works a lot like the main one, which you can find at :
https://github.com/julienp17/WaveMirror/blob/master/raspberryPi/waveMirror/waveMirror.py
The difference is that we do not get the image by the camera, and we display
the image along with its grid and grayscale values.

"""

import psutil
from PIL import Image, ImageDraw, ImageFont
from PIL.Image import *
from time import sleep

divL = 12 # The output width
divH = 10 # The output height

# Below are the paths of each picture
happy = "pictures/smileyHappy.png"
neutral = "pictures/smileyNeutral.png"
sad = "pictures/smileySad.png"

# We store them in a table, and use an index to cycle between them
mood = [happy, neutral, sad]
expression = 0

# We also initialize a font for each value that will be displayed
fnt = ImageFont.truetype('Pillow/Tests/fonts/FreeMono.ttf', 20)

while True:

	# First, we get the path of the correct smiley
	if expression == 3:
		expression = 0
	smiley = mood[expression]
	expression += 1

	# Then we open it, and convert it in black & white to get a brightness  
	# value (0 to 255) instead of an RGB one (r, g, b)
	image = open(smiley).convert('L')

	# We calculate the width and height of each square in the grid
	# The int type may left some pixels not in squares, but we can't have
	# float pixel values
	(l, h) = image.size
	tailleH = int(h/divH)
	tailleL = int(l/divL)

	# Initialize Image.Draw to be able to draw on the image later
	draw = ImageDraw.Draw(image)

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
					coordX = x + pixLDepart
					coordY = y + pixHDepart
					valPixCourant = Image.getpixel(image, (coordX, coordY))
					sommeValPix += valPixCourant
					a += 1

			# Finally, we divide the sum of gray in the square by the number
			# of pixels the square have, to get its average greyscale value
			moyValPix = int(sommeValPix/a) 

			# We draw the square on the image
			draw.rectangle(((pixLDepart, pixHDepart), (pixLFinal, pixHFinal)), outline="red")

			# Based on the grayscale value, we will write it either black or
			# white to make it visible
			if moyValPix > 165 :
				text_color = "black"
			else:
				text_color = "white"

			# At last, we write the grayscale value in the middle of the square
			draw.text(((pixLDepart+pixLFinal)/2, (pixHDepart+pixHFinal)/2), str(moyValPix), fill=text_color, font=fnt)

			# Let the program rest up a bit
			sleep(0.001)

	# When each square has been drawn and each greyscale value have been
	# written in them, we show the image to the user 
	image.show() # The image is displayed by ImageMagick

	# Close the image after 3 seconds
	sleep(3)
	for proc in psutil.process_iter():
		if proc.name() == "display":
			proc.kill()
