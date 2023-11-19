//
//    FILE: Calibrate code
//  AUTHOR: John Ferguson building on work of Rob Tillaart, x and y
// PURPOSE: Calibrate installation
//    DATE: 2023-Nov- 17
// AS5600 lib - https://github.com/RobTillaart/AS5600
// Adafruit lib SH110X
// How to use
// Build the sensor and install it in glider
// ensure the sensor rotates clockwise, ie, the number printed in the terminal window increases as you go from land flap to speed flap
// Upload Calibrate sketch with sensor fitted in glider, keep laptop attached to sensor with this code window and the serial monitor window opened, set the baud rate of serial monitor
// to 115200 baud
// Make a note of the position number (serial monitor window) for every flap position
// quit program, open the Word doc
// 


/* AS5600 includes */
#include "AS5600.h"
#include "Wire.h"
AS5600 as5600;   //  use default Wire

/* 128 x 64 Oled includes */

#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Fonts/FreeSansBold12pt7b.h>

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
//#define correction
//static uint32_t correction = 0;
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* END of 128 x 64 Oled includes */

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);

  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  // default, just be explicit.

  Serial.println(as5600.getAddress());

  //  as5600.setAddress(0x40);  // AS5600L only

  int b = as5600.isConnected();
  Serial.print("Encoder connected: ");
  Serial.println(b);

  delay(1000);
/* added 128x64 Oled setup */

   delay(250); // wait for the OLED to power up
  display.begin(i2c_Address, true); // Address 0x3C default
 //display.setContrast (0); // dim display
 
  display.display();
  delay(250);

  // Clear the buffer.
  display.clearDisplay();
  display.setFont(&FreeSansBold12pt7b);
  //display.setFont(&FreeSans9pt7b);
}




void loop()
{
  static uint32_t lastTime = 0;
  int pos = 0;                  // init vars
  int corr = 3650;              // init var and set YOUR corr value
  int maxsensorval = 4096;      // max possible sensor value of 4096 points per revolution


  //  update every 100 ms
    if (millis() - lastTime >= 100)
  {
    lastTime = millis();
    pos = as5600.readAngle() - corr;

    if (pos < 0)
    {
      pos = maxsensorval - corr + as5600.readAngle();
    }

  // enable next three lines to debug via serial monitor
      Serial.print(as5600.readAngle());
      Serial.print("\t");
      Serial.print(pos);

      Serial.println();

    // read angle goes 0 to 4096 then resets to 0
  }

}


// -- END OF FILE --