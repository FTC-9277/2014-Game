//Set to Christmas/Sarajevo 12/24 by Trans-Siberian Orchestra. 
//BPM is 186.4 by my count.
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_LSM303.h>
#include <EEPROM.h>

#define buttonRed 4
#define buttonBlue 5
#define buttonAux 6

#define stripPin 9
#define brightness 255

#define beat 321.888412

boolean armed = true;
byte offset = 0;
int i, j;
int r, g, b;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(120, stripPin, NEO_GRB + NEO_KHZ800);

void setup()
{
  strip.begin();
  strip.show();
  
  randomSeed(analogRead(A1));
  
  pinMode(buttonRed, INPUT_PULLUP);
  pinMode(buttonBlue, INPUT_PULLUP);
  pinMode(buttonAux, INPUT_PULLUP);
  
  
}

void loop()
{
  if(millis() % beat == offset)
  {
    setEntireStrip(0, 0, 0);
    strip.setPixelColor(millis()/1000 % beat, 255, 0, 0);
    strip.show();
  }
  
  if(digitalRead(buttonRed) == LOW && armed)
  {
    offset = millis() % beat;
    armed = false;
  }
  
  if(digitalRead(buttonRed) == HIGH)
  {
    armed = true;
  }
}

void setEntireStrip(int r, int g, int b)
{
  for(i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();
}
