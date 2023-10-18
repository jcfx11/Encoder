//
//    FILE: AS5600_position.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2022-12-20


#include "AS5600.h"
#include "Wire.h"

AS5600 as5600;   //  use default Wire


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
}


void loop()
{
  static uint32_t lastTime = 0;

  //  set initial position
  as5600.getCumulativePosition();

  //  update every 250 ms
    if (millis() - lastTime >= 250)
  {
    lastTime = millis();
    Serial.print(as5600.getCumulativePosition());
    Serial.print("\t");
    Serial.println(as5600.getRevolutions());

    // put the encoder values and labels here
    if
    {
        // text display tests
        display.setTextSize(6);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(10, 10);
       display.println(" 6");
       display.display();
       delay(2000);
       display.clearDisplay();


    }



  }



}


// -- END OF FILE --
