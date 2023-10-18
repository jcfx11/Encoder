/* OLED_BOURNS_ACE128 Sketch for Arduino MEGA 2560
 * This Sketch Shows Bourns Encoder Value on OLED Display
 * Arduino Sketch will clear the Screen blank for 1 second
 * Then will show ACE128 Splash Screen for 3 seconds
 * Then will show Bourns Encoder Value starting at 0
 * Clockwise Positive Values
 * Counter-Cloakwise Negative Values when below 0
 * Connect Encoder to Pins 46,47,48,49,50,51,52,53 on MEGA
 * Connect Encoder to Pins 2,3,4,5,6,7,8,9 on Uno
 * ACE128 Library at: https://github.com/arielnh56/ACE128

 * Amended by JF for Uno and ACE
 */

// OLED Display
#include <SPI.h> // added but no effect
#include <Wire.h>
// #include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h> // change driver for my cheap chip

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
// #define uint8_t 
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
// Include the Bourns EAW Encoder ACE128 library
#include <ACE128.h>  // Library info at: https://github.com/arielnh56/ACE128

// Include the Bourns EAW Encoder mapping
#include <ACE128map12345678.h> // Mapping for ACE128 Encoder pin order 12345678

// Attach to Arduino MEGA's pins 46,47,48,49,50,51,52,53 to Encoder pins 1,2,3,4,5,6,7,8
ACE128 myACE(2,3,4,5,6,7,8,9, (uint8_t*)encoderMap_12345678); // Line used for Arduino Mega2560

// Variable to hold multiturn value of encoder (-32768 to 32767)
int16_t multiturn_encoder_value;  
int16_t lpos_encoder_value; 
int16_t rawPos;

void setup() {
  Serial.begin(9600); // initialize the encoder library
  myACE.begin(); // initialize the encoder library

//  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
 //   Serial.println(F("SSD1306 allocation failed"));
 //   for(;;);
 }

  // Clear Display (Blank)for 1 second
  display.clearDisplay();
  display.display();
  delay(1000);  
  
  display.setTextSize(3);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(10, 18);

   Display 3 second Splash Screen
  display.println("ACE128");
  display.display(); 
  delay(3000);   
}



void loop() {
  multiturn_encoder_value = myACE.mpos();  // Value from encoder
  lpos_encoder_value = myACE.pos();  // static value
  rawPos = myACE.rawPos();
 // if (multiturn_encoder_value <0) { multiturn_encoder_value = 0;}
// Displays Bourns Encoder Value on Serial Monitor
  Serial.print("Encoder: ");
  Serial.print(multiturn_encoder_value);
  Serial.print(" Lpos  ");
  Serial.print(lpos_encoder_value);
  Serial.print(" Rawpos ");
   Serial.print(rawPos);
  Serial.println("");

  delay(100);
  display.clearDisplay();
  
  display.setTextSize(3);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(10, 18);

  // Displays Bourns Encoder Value starting at 0
  // The test values will need to be determined AFTER installing the sensor
  // numbers will be specific to the glider
  
  if (rawPos >= 0 && rawPos <3 )display.println("Land"); // Landing flap selected
  if (rawPos >= 3 && rawPos <7 )display.println("Flap 6"); // Flap 6 
  if (rawPos >= 7 && rawPos <11 )display.println("Flap 5"); // Flap 5
  if (rawPos >= 11 && rawPos <15 )display.println("Flap 4"); // Flap 4
  if (rawPos >= 15 && rawPos <19 )display.println("Flap 3"); // Flap 3
  if (rawPos >= 19 && rawPos <23 )display.println("Flap 2"); // Flap 2
  if (rawPos >= 23 && rawPos <27 )display.println("Flap 1"); // Flap 1


  display.display(); 
}

// Example Sketch DONE 