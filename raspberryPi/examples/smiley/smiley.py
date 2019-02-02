# -*-coding:Utf-8 -*

# This programm shows 2 differents images every 3 seconds,
# in this case a happy and a sad smiley,  in a infinite loop.
# It displays their grayscale values and serve as eye-candy
# for the day of our presentation.

import psutil
from PIL import Image, ImageDraw, ImageFont
from PIL.Image import *
from time import sleep

fnt = ImageFont.truetype('Pillow/Tests/fonts/FreeMono.ttf', 20)
hauteur = 0
longeur = 0
divH = 10
divL = 12
happy = "pictures/smileyHappy.png"
neutral = "pictures/smileyNeutral.png"
sad = "pictures/smileySad.png"
mood = [happy, neutral, sad]
expression = 0

while True:
	if expression == 3:
		expression = 0
	smiley = mood[expression]
	expression += 1
	image = open(smiley).convert('L')
	(l, h) = image.size
	tailleH = int(h/divH)
	tailleL = int(l/divL)
	draw = ImageDraw.Draw(image)

	for hauteur in range(divH):
		pixHDepart = tailleH * hauteur
		pixHFinal = tailleH * (hauteur + 1)

		for longueur in range(divL):
			pixLDepart = tailleL * longueur
			pixLFinal = tailleL * (longueur + 1)

			a = 0
			sommeValPix = 0
			x = 0
			y = 0

			for y in range(tailleH):
				for x in range(tailleL):
					coordX = x + pixLDepart
					coordY = y + pixHDepart
					valPixCourant = Image.getpixel(image, (coordX, coordY))
					sommeValPix += valPixCourant
					a += 1

			moyValPix = int(sommeValPix/a)
			draw.rectangle(((pixLDepart, pixHDepart), (pixLFinal, pixHFinal)), outline="red")
			if moyValPix > 165 :
				filou = "black"
			else:
				filou = "white"
			draw.text(((pixLDepart+pixLFinal)/2, (pixHDepart+pixHFinal)/2), str(moyValPix), fill=filou, font=fnt)
			#sleep(0.001)
	image.show()
	sleep(3)
	for proc in psutil.process_iter():
		if proc.name() == "display":
			proc.kill()
