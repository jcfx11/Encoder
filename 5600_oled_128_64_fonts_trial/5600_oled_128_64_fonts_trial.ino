//
//    FILE: Flap sensor and display.ino
//  AUTHOR: John Ferguson building on work of Rob Tillaart, x and y
// PURPOSE: Glider flaps encoder sensor and flap position display
//    DATE: 2023-Sept- 1
// AS5600 lib - https://github.com/RobTillaart/AS5600
// Adafruit lib SH110X

/* Parts list

AS5600 encoder          - https://www.amazon.co.uk/dp/B09GLPV6WB?psc=1&ref=ppx_yo2ov_dt_b_product_details
Oled 128x64             - https://www.amazon.co.uk/gp/product/B074N9VLZX/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1
Bearing                 - generic 608 roller skate bearing, ebay or amazon
3d print parts bearing  - baseplate and bearing mount from here -> https://github.com/scottbez1/AS5600Knob
Lever arm here          - https://www.tinkercad.com/things/aveWrb0Cxmn-flap-sensor-lever/edit copy and remix for your own purposes
M3 nut and bolt
Veroboard       - ebay or amazon

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
  Serial.begin(115200);
  //Serial.println(__FILE__);
 // Serial.print("AS5600_LIB_VERSION: ");
 // Serial.println(AS5600_LIB_VERSION);

  //  ESP32
  //  as5600.begin(14, 15);
  //  AVR
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

  //  update every 100 ms
    if (millis() - lastTime >= 100)
  {
    lastTime = millis();
  // /* enable next three lines to debug via serial monitor
      Serial.print(as5600.readAngle());
      Serial.print("\t");
      Serial.println(as5600.getRevolutions());
  // */
    display.display();
    display.clearDisplay();


    // put the encoder values and labels here - Schleicher in this case - labels are Land, 6, 5, 4, 3, 2, 1
    // Schempp labels are; Land, +2, +1, 0, -1, -2 (best guess)
    // read angle goes 0 to 4096 then resets to 0, cumulative angle keeps incrementing and does not wrap round

    if (as5600.readAngle() > 0 && as5600.readAngle() < 200)
    
     // read angle range is 0 to 4096 then resets to 0
    {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 50);
        display.println("Land");
        display.display();
       
    }
 
    if (as5600.readAngle() > 200 && as5600.readAngle() < 400)
    {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 50);
        display.println(" FL 6");
        display.display();
       
    }
 
    if (as5600.readAngle() > 400 && as5600.readAngle() < 600)
    {
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 50);
        display.println(" FL 5");
        display.display();
       
    }
 
    if (as5600.readAngle() > 600 && as5600.readAngle() < 800)
    {
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 50);
        display.println(" FL 4");
        display.display();
       
    }

    if (as5600.readAngle() > 800 && as5600.readAngle() < 1000)
    {
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 50);
        display.println(" FL 3");
        display.display();
       
    }

    if (as5600.readAngle() > 1000 && as5600.readAngle() < 1200)
    {
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 50);
        display.println(" FL 2");
        display.display();
       
    }

    if (as5600.readAngle() > 1200 && as5600.readAngle() < 1400)
    {
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0, 50);
        display.println(" FL 1");
        display.display();
       
    }

    
  }



}


// -- END OF FILE --
