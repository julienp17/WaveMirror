The **examples** directory contains other scripts based on the main program, to test standalone features (test the camera, I2C, smiley eye-candy).

Every script is made to work for python2.7

**Remote I/O ERROR :** 
Check for I2C connectivity with `i2cdetect -y 1` on the Raspberry Pi. Check for Arduino addresses in both Python code and Arduino code. Check connections. Make sure values don't get sent too fast