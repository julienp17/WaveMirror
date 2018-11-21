# -*-coding:Utf-8 -*

import smbus
import time

# Remplacer 0 par 1 si nouveau Raspberry
bus = smbus.SMBus(1)
address = 0x03

print("Envoi de la valeur 3")
bus.write_byte(address, 3)
# Pause de 1 seconde pour laisser le temps au traitement de se faire
time.sleep(1)
reponse = bus.read_byte(address)
print "La reponse de l'arduino : ", reponse