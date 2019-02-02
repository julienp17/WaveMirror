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

# Imports
import smbus
import picamera
from PIL import Image, ImageDraw, ImageFont
from PIL.Image import *
from io import BytesIO
from time import sleep

# Déclaration des variables
bus = smbus.SMBus(1)
camera = picamera.PiCamera()
stream = BytesIO()
fnt = ImageFont.truetype('Pillow/Tests/fonts/FreeMono.ttf', 20)
camera.resolution = (800, 600)
#camera.start_preview()
hauteur = 0
longeur = 0
divH = 10
divL = 12

# Début du programme
for i in range(2):
    case = 0
    arduino = 2 
    stream.seek(0)
    camera.capture(stream, format="jpeg")
    image = open(stream).convert('L')   
    (l, h) = image.size
    tailleH = int(h/divH)
    tailleL = int(l/divL)
    draw = ImageDraw.Draw(image)
    print("Passage de {0}*{1} à {2}*{3}\n1 case = {4}*{5} pixels".format(l,h,divL,divH,tailleL,tailleH))

    for hauteur in range(divH):
             pixHDepart = tailleH * hauteur
             pixHFinal = tailleH * (hauteur + 1)

             for longueur in range(divL):
                 pixLDepart = tailleL * longueur
                 pixLFinal = tailleL * (longueur + 1)

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
                 
                 draw.rectangle(((pixLDepart, pixHDepart), (pixLFinal, pixHFinal)), outline="red")
                 if moyValPix > 165 :
                     filou = "black"
                 else:
                     filou = "white"
                 draw.text(((pixLDepart+pixLFinal)/2, (pixHDepart+pixHFinal)/2), str(moyValPix), fill=filou, font=fnt)

                 if (case%12)+1 == 1 :
                    arduino += 1

                 case +=1
                 print("Case numéro {0} = {1}".format(case,moyValPix))
                 if arduino < 5 : # a retirer pour le programme final
                     bus.write_byte(arduino, moyValPix)
                 sleep(0.001)
    image.show()
    sleep(3)
