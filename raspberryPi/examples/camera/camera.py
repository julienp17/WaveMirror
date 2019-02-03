# -*-coding:Utf-8 -*

"""This script allows us to test the PiCamera.

You can find more information on the official Raspberry Pi's projects website:
https://projects.raspberrypi.org/en/projects/getting-started-with-picamera

Make sure the Raspberry Pi is connected to a monitor if you want to see 
the preview. The preview doesn't show on VNC.

"""

import picamera
from time import sleep

# Create object for PiCamera class
camera = picamera.PiCamera()

# Set some parameters for the camera
camera.resolution = (800, 600)
camera.brightness = 60
camera.annotate_text = 'Hi Pi User'

# Start the preview for 5 seconds
camera.start_preview()
sleep(5)

# Store the image
camera.capture('image1.jpeg')
camera.stop_preview()