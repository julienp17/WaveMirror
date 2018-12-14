# -*-coding:Utf-8 -*

import psutil
from PIL import Image
from PIL.Image import *
from time import sleep

hauteur = 0
longeur = 0
divH = 10
divL = 12
happy = True

for x in range(2):
	if happy:
		smiley = "smileyHappy.png"
		happy = False
	else:
		smiley = "smileySad.png"
		happy = True
	image = open(smiley)
	image = image.convert('L')
	(l, h) = image.size
	tailleH = int(h/divH)
	tailleL = int(l/divL)
	print(tailleH, tailleL)

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
			sleep(0.001)
	image.show()
	sleep(3)
	for proc in psutil.process_iter():
		if proc.name() == "display":
			proc.kill()


