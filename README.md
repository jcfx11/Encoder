A very simple use of an AS5600 absolute encoder to read an angle and translate that angle to a flap setting displayed on a small oled display. Builds on the work of Scott and Rob Tillart
Due to the simplicity of the project, ie, no added pusbuttons to set or increment positions, the code is very simple, but does require come ability to change the code where specified to suit your particular installation. I'm using Arduino IDE v2.x

Hardware - Arduino Uno or Nano easy. This code has been tested on both and works. The solution could be ported to any microprocessor that has an I2C bus and provides 3.3V and 5V for the sensor and Oled displays.

Needs hands on coding to calibrate and tailor the angles read to the display

Further coding to be added to the project, still a work in progress
