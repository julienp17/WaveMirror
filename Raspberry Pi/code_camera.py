# -*-coding:Utf-8 -*

### Projet Wave Mirror ###
## Science de l'Ingénieur, Lycée George Brassens, année 2018-2019 
## Professeurs : AVI Philippe, Alain BENARD 
## Eleves : PAUSE Julien (auteur de ce code), RALAMBOARIVONY Teddy, FERRERE Guillyann, GRONDIN Guillaume

# Ce programme consiste à capturer l'image d'une camera RPi, la convertir en noir et blanc, la découper en 
# portions de pixels, et envoyer la moyenne de gris de chaque portions vers des Arduino par la liaison I2C

# Ne marche que sur Python 2
# Variables à changer : divH & divL (résolution de l'image de sortie)
# Plus la résolution choisie est grande , plus l'image est nette, mais le temps de procession augmente également

# Edit 17/11/18 : rajouter l.22, 26, 35, 36, 37

# Imports
import smbus
from PIL import Image
from PIL.Image import *
from time import sleep
from picamera import picamera

# Déclaration des variables
bus = smbus.SMBus(1)
camera = PiCamera()
hauteur = 0
longeur = 0
case = 0
arduino = 0
divH = 10
divL = 12

# Début du programme
camera.resolution = (800, 600)
camera.capture('/home/pi/waveMirror.jpg')
image = open('/home/pi/waveMirror.jpg')
image = image.convert('L') # conversion en noir et blanc
(l, h) = image.size
tailleH = int(h/divH)
tailleL = int(l/divL)

for hauteur in range(divH):
         pixHDepart = tailleH * hauteur
         pixHFinal = tailleH * (hauteur + 1)

         for longueur in range(divL):
             pixLDepart = tailleL * longueur
             pixLFinal = tailleL * (longueur + 1)

             # calcul de la moyenne de chaque portion

             a = 0
             sommeValPix = 0
             y=0
             x=0

             for y in range(tailleH):
                 for x in range(tailleL):

                     coordX = x + (pixLDepart)
                     coordY = y + (pixHDepart)
                     valPixCourant = Image.getpixel(image, (coordX, coordY))
                     sommeValPix += valPixCourant
                     a += 1

             moyValPix = int(sommeValPix / a) #la moyenne de gris pour chaque portion

             if (case%12)+1 == 1 :
             	arduino += 1   

             case +=1
             bus.write_byte((arduino+2), moyValPix)
             sleep(0.001)