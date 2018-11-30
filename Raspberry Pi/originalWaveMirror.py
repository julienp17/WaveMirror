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
from PIL import Image
from PIL.Image import *
from time import sleep

def pixelisation(camera):

     camera = camera.convert('L') # conversion en noir et blanc
     Image.show(camera) # verification

     sleep(1)

     (l, h) = camera.size

     divH = 10
     divL = 12

     tailleH = int(h/divH)
     tailleL = int(l/divL)

     hauteur = 0
     longeur = 0
     case = 0
     arduino = 0

     print("Passage de {0}*{1} à {2}*{3}\n1 case = {4}*{5} pixels".format(l,h,divL,divH,tailleL,tailleH)) 

     # découpage en portions

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
                     valPixCourant = Image.getpixel(camera, (coordX, coordY))
                     sommeValPix += valPixCourant
                     a += 1

             moyValPix = int(sommeValPix / a) #la moyenne de gris pour chaque portion
             
             # debug

             if (case%12)+1 == 1 :
                arduino += 1
                if (arduino + 2) < 10:
                    addresse = ('0x0' + str(arduino + 2))
                else:
                    addresse = ('0x' + str(arduino+2))

                print('{2}\nArduino n{0} - addresse : {1}\n{2}'.format(arduino,addresse,'-'*30))      

             case +=1
             print("Case numéro {0} = {1}".format(case,moyValPix))

             # ecriture de la moyenne pour chaque portion (seulement utile pour debug GUI)

             for y in range(tailleH):
                 for x in range(tailleL):

                     coordX = x + (pixLDepart)
                     coordY = y + (pixHDepart)

                     Image.putpixel(camera, (coordX, coordY), moyValPix)
     Image.show(camera)
     sleep(1)

camera=open("lion.jpeg")
Image.show(camera)
sleep(1)
pixelisation(camera)


