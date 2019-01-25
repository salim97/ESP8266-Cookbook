#include <Arduino.h>
#include <TinyGPS++.h>                                  // Tiny GPS Plus Library
#include <SoftwareSerial.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9340.h>

/*
 GPS NEO 6M
 VCC - 3v3
 GND - GND
 TX - D1
 RX - D0
*/

/*
  TFT 2.2 SPI
  D5 - CLK
  D6 - MISO
  D7 - MOSI
  D8 - cs

  D2 - RST
  D4 - DC

*/
#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// These are the pins used for the UNO
// for Due/Mega/Leonardo use the hardware SPI pins (which are different)
#define _sclk  14
#define _miso  12
#define _mosi  13
#define _cs  15
#define _dc  D4
#define _rst  D2

// Using software SPI is really not suggested, its incredibly slow
//Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _mosi, _sclk, _rst, _miso);
// Use hardware SPI
Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);



static const int RXPin = D1, TXPin = D0;                // Ublox 6m GPS module to pins 12 and 13
static const uint32_t GPSBaud = 9600;                   // Ublox GPS default Baud Rate is 9600
TinyGPSPlus gps;                                        // Create an Instance of the TinyGPS++ object called gps
SoftwareSerial ss(RXPin, TXPin);                        // The serial connection to the GPS device
static void smartDelay(unsigned long ms)  ;
void setup() {
  // put your setup code here, to run once:
   ss.begin(GPSBaud);                                    // Set Software Serial Comm Speed to 9600
   Serial.begin(115200);
   tft.begin();

}
int i = 0 ;
void loop() {

  smartDelay(500);

      // Serial.println("=====================================") ;
      // Serial.print("Latitude  : ");
      // Serial.println(gps.location.lat()) ;
      //
      // Serial.print("Longitude   : ");
      // Serial.println(gps.location.lng()) ;
      //
      // Serial.print("Satellites   : ");
      // Serial.println(gps.satellites.value()) ;
      //
      // Serial.print("Elevation   : ");
      // Serial.println(gps.altitude.feet()) ;
      //
      // Serial.print("Time UTC  : ");
      // Serial.print(gps.time.hour());
      // Serial.print(":");
      // Serial.print(gps.time.minute());
      // Serial.print(":");
      // Serial.println(gps.time.second());
      //
      // Serial.print("Heading   : ");
      // Serial.println(gps.course.deg()) ;
      //
      // Serial.print("Speed   : ");
      // Serial.println(gps.speed.mph()) ;



  tft.setRotation(3);

  tft.fillScreen(ILI9340_BLACK);
  tft.setCursor(0, 0);

  tft.setTextSize(4);

  tft.setTextColor(ILI9340_GREEN);
  tft.print("UTC: ");
  tft.print(gps.time.hour());
  tft.print(":");
  tft.print(gps.time.minute());
  tft.print(":");
  tft.println(gps.time.second());
  tft.println();

  tft.setTextColor(ILI9340_RED);
  tft.print("Lat: ");
  tft.println(gps.location.lat()) ;

  tft.setTextColor(ILI9340_YELLOW);
  tft.print("Lon: ");
  tft.println(gps.location.lng()) ;

  tft.setTextColor(ILI9340_BLUE);
  tft.print("alt: ");
  tft.println(gps.altitude.feet()) ;

  //tft.setTextColor(ILI9340_WHITE);
  //tft.println("    "+String(i++));

  //delay(2000);



}

static void smartDelay(unsigned long ms)                // This custom version of delay() ensures that the gps object is being "fed".
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
