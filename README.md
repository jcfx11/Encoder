A very simple use of an AS5600 absolute encoder to read an angle and translate that angle to a flap setting displayed on a small oled display. Builds on the work of Scott and Rob Tillart
Due to the simplicity of the project, ie, no added pusbuttons to set or increment positions, the code is very simple, but does require come ability to change the code where specified to suit your particular installation. I'm using Arduino IDE v2.x

Hardware - Arduino Uno or Nano Every. This code has been tested on both and works. The solution could be ported to any microprocessor that has an I2C bus and provides 3.3V and 5V for the sensor and Oled displays.

AS5600 3.3V absolute encoder, 1.3 inch 5V Mono OLED display from Ebay or similar, 3d printed parts, piece of veroboard, and a "shield" for your microprocessor to enable easy board connections.

Needs hands on coding to calibrate and tailor the angles read to the display

The two sensor arms are examples, I expect you will need to tailor the length for example to suit your particular installation.
https://www.tinkercad.com/things/aveWrb0Cxmn-flap-sensor-lever

V 1 is complete, ideally V2 will use interupt handling to read the sensor rather than the timer in use now.

Please excuse my wonky soldering and photos, I'm on holiday.
