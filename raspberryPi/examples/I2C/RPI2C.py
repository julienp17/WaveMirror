# -*-coding:Utf-8 -*

import smbus
from time import sleep

bus = smbus.SMBus(1)
# les addresses arduino vont de 0x03 à 0x77 (hexadecimal)
arduino1 = 0x03
arduino2 = 0x04

nombre = int(input("Entrer entre 0-255: "))
bus.write_byte(3, nombre)
bus.write_byte(4, nombre + 5)

# Pause de 1 seconde pour laisser le temps au traitement de se faire
sleep(1)
