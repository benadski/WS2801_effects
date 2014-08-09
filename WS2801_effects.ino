#include "SPI.h"
#include "Adafruit_WS2801.h"

/*****************************************************************************
Example sketch for driving Adafruit WS2801 pixels!


  Designed specifically to work with the Adafruit RGB Pixels!
  12mm Bullet shape ----> https://www.adafruit.com/products/322
  12mm Flat shape   ----> https://www.adafruit.com/products/738
  36mm Square shape ----> https://www.adafruit.com/products/683

  These pixels use SPI to transmit the color data, and have built in
  high speed PWM drivers for 24 bit color per pixel
  2 pins are required to interface

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution

*****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
uint8_t dataPin  = 2;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 3;    // Green wire on Adafruit Pixels

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
const uint8_t NumberOfPixels = 25;
Adafruit_WS2801 strip = Adafruit_WS2801(NumberOfPixels, dataPin, clockPin);

// Optional: leave off pin numbers to use hardware SPI
// (pinout is then specific to each board and can't be changed)
//Adafruit_WS2801 strip = Adafruit_WS2801(25);

// For 36mm LED pixels: these pixels internally represent color in a
// different format.  Either of the above constructors can accept an
// optional extra parameter: WS2801_RGB is 'conventional' RGB order
// WS2801_GRB is the GRB order required by the 36mm pixels.  Other
// than this parameter, your code does not need to do anything different;
// the library will handle the format change.  Examples:
//Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin, WS2801_GRB);
//Adafruit_WS2801 strip = Adafruit_WS2801(25, WS2801_GRB);


//PUSHBUTTON ON I/O 4, NC TO GND <- NOT USED NOW!


uint8_t Col_set = 3;    //Colorset setting


void setup() {
    
  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
  randomSeed(analogRead(2));
}


void loop() {
  // Some example procedures showing how to display to the pixels
  
  //colorWipe(Color(255, 0, 0), 50);
  //colorWipe(Color(0, 255, 0), 50);
  //colorWipe(Color(0, 0, 255), 50);
  //rainbow(20);
  melon(20);
  fire(5);
  welding(8);
  grinding(32);
  if (Col_set > 4) Col_set = 0; else Col_set++;
  
}

// Melon style green/yellow/white random blinky fader
void melon(uint8_t wait) {
  int i, j;
  uint8_t pixel[NumberOfPixels];  //New color
  uint8_t nixel[NumberOfPixels];  //Old colour
  int16_t temp;
  
  //  
  for (j=0; j < 40; j++) {   
    for (uint8_t x = 0; x < NumberOfPixels; x++) { 
      pixel[x] = random(255);
    }
    for (uint8_t x = 0; x < 64; x++) { 
      for (i=0; i < NumberOfPixels; i++) {
        temp = (pixel[i] * x + nixel[i] * (63 - x)) / 63;
        strip.setPixelColor(i, Mellooon(temp));
      }  
      strip.show();   // write all the pixels out
      delay(wait);
    }
    for (uint8_t x = 0; x < NumberOfPixels; x++) { 
      nixel[x] = pixel[x];
    }
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  if (Col_set == 0)
  {  
    c = r;
    c <<= 8;
    c |= g;
    c <<= 8;
    c |= b;
  }
  if (Col_set == 1)
  {  
    c = g;
    c <<= 8;
    c |= b;
    c <<= 8;
    c |= r;
  }
  if (Col_set == 2)
  {  
    c = b;
    c <<= 8;
    c |= r;
    c <<= 8;
    c |= g;
  }
  if (Col_set == 3)
  {  
    c = r;
    c <<= 8;
    c |= b;
    c <<= 8;
    c |= g;
  }
  if (Col_set == 4)
  {  
    c = g;
    c <<= 8;
    c |= r;
    c <<= 8;
    c |= b;
  }
  if (Col_set == 5)
  {  
    c = b;
    c <<= 8;
    c |= g;
    c <<= 8;
    c |= r;
  }
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transitions of white yellow and green.
uint32_t Mellooon(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255, 255, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 0);
  }
}

void welding(uint8_t wait)
{
  uint8_t pixel[NumberOfPixels];  //Welding
  uint8_t nixel[NumberOfPixels];  //Afterglow
  int16_t temp; 

  for (uint16_t weld = 0; weld < (30000 / wait); weld++)
  {
    for (uint8_t x = 0; x < NumberOfPixels; x++)
    {
      //If still welding
      if (pixel[x] > 0)
      {
        pixel[x]--;
        if (pixel[x] == 0) nixel[x] = 255;
        strip.setPixelColor(x, Weld(127 + random(128)));
      }
      
      //Set new welding period
      if ((pixel[x] == 0) && (nixel[x] == 0)) pixel[x] = 63 + random(192);
       
      //Afterglow or pause 
      if (nixel[x] > 0)
      {
        if (nixel[x] == 128) nixel[x] -= random(128);
        if (nixel[x] > 128) {
          nixel[x]--;
          strip.setPixelColor(x, Weld(nixel[x] - 128));
        } else {
          if (random(4) == 0) nixel[x]--; //Every 4 cycles or so...
          strip.setPixelColor(x, 0);
        }
      }
    }
    strip.show();   // write all the pixels out
    delay(wait);
  }   
}

void fire(uint8_t wait)
{
  uint8_t pixel[NumberOfPixels];  //Displayed pixel value
  uint8_t nixel[NumberOfPixels];  //Not displayed (previous value)
  int16_t temp; 

  for (uint16_t flame = 0; flame < (30000 / 8 / wait); flame++)
  {
    //Set color of bases of the flames
    pixel[0] = 127 + random(128);
    pixel[24] = 127 + random(128);
    
    //Color each pixel a little bit dimmer than the previous lower pixel
    for (uint8_t x = 0; x < 11; x++)
    {
      temp = nixel[x] - 16 - random(8);
      if (temp < 0) temp = 0;
      pixel[x + 1] = temp;
      temp = nixel[24 - x] - 16 - random(8);
      if (temp < 0) temp = 0;
      pixel[23 - x] = temp;
    }

    //For the middle pixel of the 25 LED pixel strand, combine the values.
    temp = (nixel[11] | nixel[13]) - 16 - random(12);
    if (temp < 0) temp = 0;
    pixel[12] = temp % 256;
   
    //Do some fading from old to new colour to make it look nice
    for (uint8_t fade = 0; fade < 8; fade++)
    {
      for (uint8_t x = 0; x < NumberOfPixels; x++)
      {
        temp = (pixel[x] * fade + nixel[x] * (7-fade)) / 7;
        strip.setPixelColor(x, Flame(temp % 256));
      }
      strip.show();   // write all the pixels out
      delay(wait);    
    }
    
    //Copy the new values to the old for the next run.
    for (uint8_t x = 0; x < NumberOfPixels; x++)
    {
      nixel[x] = pixel[x];
    }    
  }
}

void grinding(uint8_t wait)
{
   for (uint16_t y = 0; y < 1000; y++) //Grinding
   {
     for (uint8_t x = 0; x < NumberOfPixels; x++)
     {
       strip.setPixelColor(x, Spark(random(255)));
     }
     strip.show();
     delay(wait);
   }
}


//Input a value 0 to 255 to get a color value.
//Fire color mapping, returns 24-bit color.
uint32_t Flame(uint8_t Map)
{
  if (Map > 240) {
   return Color(255, 255, 85);
  } else if (Map > 200) {
   Map -= 200;
   return Color(255, 255, Map * 2);
  } else if (Map > 73) {
   Map -= 73;
   return Color(255, Map * 2, 0);
  } else if (Map > 10) {
   Map -= 10;
   return Color(Map * 4, 0, 0);
  } else {
   return Color(0, 0, 0);
  }       
}

//Input a value 0 to 255 to get a color value.
//Weld sparks and afterglow color mapping, returns 24-bit color.
uint32_t Weld(uint8_t Map)
{
  if (Map > 128) {
    Map -= 128;
    return Color(Map, Map, 255);
  } else if (Map > 64) {
    Map -= 64;
    return Color(Map + 24, Map / 3, 0);
  } else {
    return Color(Map / 3 , 0, 0);
  }
}

//Flash, orange to red spark.
uint32_t Spark(uint8_t Map)
{
  if (Map > 64)
  {
    return 0;
  }
  if (Map > 56)
  {
    return Color(255, 255, (Map - 56) * 16);
  }
  else if (Map > 24)
  {
    Map -= 24;
    return Color(128 + Map * 4, Map * 8, 0);
  } else {
    return Color(Map * 4, 0, 0);
  }
}
