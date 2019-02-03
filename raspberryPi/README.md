The **waveMirror** directory contains the program used for the project.

The **examples** directory only contains parts of the code, to test standalone features (picamera, I2C, side project).

Every script is made to work for python2.7

**Remote I/O ERROR :** 
- check for I2C connectivity with `i2cdetect -y 1` on the Raspberry Pi, or check for Arduino addresses in both python code and arduino code.