//
//    FILE: AS5600_position.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2022-12-20

// setup for AS5600

#include "AS5600.h"

#include "Wire.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
AS5600 as5600;   //  use default Wire

//AS5600 setup ends

// Oled screen setup

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup()
{
  display.begin(i2c_Address, true); // Address 0x3C default
  display.setContrast (1); // dim display
  display.setTextSize(8);
  display.setTextColor(SH110X_WHITE);

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);




  //  ESP32
  //  as5600.begin(14, 15);
  //  AVR
  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  // default, just be explicit.

  Serial.println(as5600.getAddress());

  //  as5600.setAddress(0x40);  // AS5600L only

  int b = as5600.isConnected();
  Serial.print("Connect: ");
  Serial.println(b);

  delay(1000);
  display.clearDisplay();
}


void loop()
{
  static uint32_t lastTime = 0;

  //  set initial position
  as5600.getCumulativePosition();
 // as5600.resetPosition()
 // as5600.

   display.clearDisplay();

  //  update every half second ms
  //  should be enough up to ~200 RPM
  if (millis() - lastTime >= 500)
  {
    //lastTime = millis();
    Serial.print(as5600.getCumulativePosition());
    Serial.print("\t");
    Serial.println(as5600.getRevolutions());
    //display.clearDisplay();

    if (as5600.getCumulativePosition() >400)
    {
       Serial.println("Flapsssssssssssssssssssssssss");
       //display.clearDisplay();
       display.println(" 6");
       display.display();
/*     
   display.setCursor(0, 0);
      //display.println("");
      display.println(" 6");
      display.display();
     //delay(200);
     display.clearDisplay();
 */   }
  }



  
}


// -- END OF FILE --
