# -*-coding:Utf-8 -*

"""This script allows us to test the PiCamera by showing what it captures.

You can find more information on the official Raspberry Pi's projects website:
https://projects.raspberrypi.org/en/projects/getting-started-with-picamera

Make sure the Raspberry Pi is connected to a monitor to see the preview. 
It doesn't work on VNC & SSH.

"""

import picamera
from time import sleep

# Create object for PiCamera class
camera = picamera.PiCamera()

# Set the resolution of the camera
camera.resolution = (800, 600)

# Start the preview endlessly
camera.start_preview()
while True:
    sleep(5)

# Stop it
camera.stop_preview()