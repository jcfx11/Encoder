//
//    FILE: Flap sensor and display.ino
//  AUTHOR: John Ferguson building on work of Rob Tillaart, x and y
// PURPOSE: Glider flaps encoder sensor and flap position display
//    DATE: 2023-Nov
// AS5600 lib - https://github.com/RobTillaart/AS5600
// Adafruit lib SH110X

/* Parts list

AS5600 encoder          - https://www.amazon.co.uk/dp/B09GLPV6WB?psc=1&ref=ppx_yo2ov_dt_b_product_details
Oled 128x64             - https://www.amazon.co.uk/gp/product/B074N9VLZX/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1
Bearing                 - generic 608 roller skate bearing, ebay or amazon
3d print parts bearing  - baseplate and bearing mount from tinkercad 
                          https://www.tinkercad.com/things/8eYcTnPwoCL-as5600-and-608-bearing-mount?sharecode=cw8v2tMz8DSdhe8cIA-GtBzGL0PlDsC3LucjUibfPgA
                          https://www.tinkercad.com/things/kjFzeW6U8p8-flap-sensor-mount-plate?sharecode=OV5DX3Oy9MLU_jf0EiqsDPxmtuYhIUuUqlG4Ay8k9ps
Lever arm here          - https://www.tinkercad.com/things/aveWrb0Cxmn-flap-sensor-lever/edit copy and remix for your own purposes
M2.5 nuts and bolts
Veroboard              - ebay or amazon
4 core and shield cable, say 4 m should do

*/

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
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* END of 128 x 64 Oled includes */

void setup()
{
 
  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  // default, just be explicit.

  delay(250); // wait for the OLED to power up
  display.begin(i2c_Address, true); // Address 0x3C default
 //display.setContrast (0); // dim display, doesn't seem to do anything
 
  display.display();
  delay(250);

  // Clear the buffer.
  display.clearDisplay();
  display.setFont(&FreeSansBold12pt7b); // set your favorite font and size - you will need to alter x and y pos dependent upon font
  //display.setFont(&FreeSans9pt7b);    // other example font
}

void loop()
{
  static uint32_t lastTime = 0; // loop timer
  int pos = 0;                  // init vars
  int corr = 3650;              // init vars
  int maxsensorval = 4096;      // max possible sensor value of 4096 points per revolution

  //  read the sensor value every 100 ms
    if (millis() - lastTime >= 100)
  {
    lastTime = millis();

    // Code block to set the random angle of the encoder to a sensible value for the LAND FLAP position, encode MUST rotate clockwise going from LAND to Speed flaps
    // corr may be left at zero if the "random" position of the sensor reads a sensible low value at LAND FLAP, eg, the range of the sensor must
    // not exceed 4096 and wrap round to zero going from LAND to Speed

    pos = as5600.readAngle() - corr;
    if (pos < 0)
    {
      pos = maxsensorval - corr + as5600.readAngle();
    }

  // clear the display ready for next label
    display.display();
    display.clearDisplay();

    // put the encoder values and labels here - Schleicher in this case - labels are Land, 6, 5, 4, 3, 2, 1
    // Schempp labels are; Land, +2, +1, 0, -1, -2 (best guess)
    // read angle goes 0 to 4096 then resets to 0, cumulative angle keeps incrementing and does not wrap round hence maxsensor val, pos and corr use
    // Example values are embedded below to show how a range of value is set including a small fudge factor to cope with any jitter or vibration in the sensor

    if (pos > 0 && pos  < 200) // land flap
    
    {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 50);
        display.println("Land"); // Oled text display
        display.display();
       
    }
 
    if (pos > 200 && pos < 400) // Flap 6
    {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 50);
        display.println(" FL 6"); // Oled text display
        display.display();
       
    }
 
    if (pos > 400 && pos < 600) // Flap 5
    {
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 50);
        display.println(" FL 5"); // Oled text display
        display.display();
       
    }
 
    if (pos  > 600 && pos < 800) // Flap 4
    {
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 50);
        display.println(" FL 4"); // Oled text display
        display.display();
       
    }

    if (pos > 800 && pos < 1000) // Flap 3
    {
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 50);
        display.println(" FL 3"); // Oled text display
        display.display();
       
    }

    if (pos > 1000 && pos < 1200) // Flap 2
    {
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 50);
        display.println(" FL 2"); // Oled text display
        display.display();
       
    }

    if (pos > 1200 && pos < 1400) // Flap 1
    {
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 50);
        display.println(" FL 1"); // Oled text display
        display.display();
       
    }

    
  }



}


// -- END OF FILE --