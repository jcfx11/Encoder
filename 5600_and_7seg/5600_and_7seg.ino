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

/* 7 seg display includes */
#include "SevSeg.h"
SevSeg sevseg;


/* END includes */

void setup()
{

  //Set to 1 for single digit display
	byte numDigits = 1;

	//defines common pins while using multi-digit display. Left empty as we have a single digit display
	byte digitPins[] = {};

	//Defines arduino pin connections in order: A, B, C, D, E, F, G, DP
	byte segmentPins[] = {3, 2, 8, 7, 6, 4, 5, 9};
	bool resistorsOnSegments = true;

	//Initialize sevseg object. Uncomment second line if you use common cathode 7 segment
	sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
	//sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);

	sevseg.setBrightness(10);
  sevseg.setChars(" ");
  sevseg.refreshDisplay(); 

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
/* added 7 seg setup */
  

}




void loop()
{
  static uint32_t lastTime = 0;

  //  update every 100 ms
    if (millis() - lastTime >= 100)
  {
    lastTime = millis();
  /* enable next three lines to debug via serial monitor
      Serial.print(as5600.readAngle());
      Serial.print("\t");
      Serial.println(as5600.getRevolutions());
   */

    // put the encoder values and labels here - Schleicher in this case - labels are L, 6, 5, 4, 3, 2, 1
    // Schempp labels are; Land, +2, +1, 0, -1, -2 (best guess)
    // read angle goes 0 to 4096 then resets to 0, cumulative angle keeps incrementing and does not wrap round

    if (as5600.readAngle() > 0 && as5600.readAngle() < 200)
    
     // read angle goes 0 to 4096 then resets to 0
    {
     sevseg.setChars("L");
     sevseg.refreshDisplay(); 
       
    }
 
    if (as5600.readAngle() > 200 && as5600.readAngle() < 400)
    {
     sevseg.setNumber(6);     
     sevseg.refreshDisplay(); 
       
    }
 
    if (as5600.readAngle() > 400 && as5600.readAngle() < 600)
    {
     sevseg.setNumber(5);     
     sevseg.refreshDisplay(); 
       
    }
 
    if (as5600.readAngle() > 600 && as5600.readAngle() < 800)
    {
     sevseg.setNumber(4);     
     sevseg.refreshDisplay(); 
       
    }

    if (as5600.readAngle() > 800 && as5600.readAngle() < 1000)
    {
        sevseg.setNumber(3);     
     sevseg.refreshDisplay(); 
       
    }

    if (as5600.readAngle() > 1000 && as5600.readAngle() < 1200)
    {
     sevseg.setNumber(2);     
     sevseg.refreshDisplay(); 
    }

    if (as5600.readAngle() > 1200 && as5600.readAngle() < 1400)
    {
     sevseg.setNumber(1);     
     sevseg.refreshDisplay(); 
    }

    
  }



}


// -- END OF FILE --
