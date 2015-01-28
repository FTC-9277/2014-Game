#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_LSM303.h>
#include <EEPROM.h>

#define buttonRed 8
#define buttonBlue 12
#define buttonAux 6

#define stripPin 9
#define brightness 255

int i, j, k;
int a, b, c;
long targetMillis;
boolean isBlue, isNeutral;
uint32_t allianceColor;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(72, stripPin, NEO_GRB + NEO_KHZ800);
Adafruit_LSM303 gyro;

void setup()
{
  randomSeed(analogRead(A1));
  pinMode(buttonRed, INPUT_PULLUP);
  pinMode(buttonBlue, INPUT_PULLUP);
  pinMode(buttonAux, INPUT_PULLUP);
  
  gyro.begin();
  strip.begin();
  strip.setBrightness(brightness);
  strip.show();
  
  bootupAnimation2();
  
  bootloader(8);
}

void loop()
{
  sparkle(60);
  flashFadeThroughWhite(60);
  insanityChase(60);
  if(!isNeutral)
  {
    insanity(20);
  }
}

void bootloader(long time)
{
  boolean red = false;
  boolean blue = false;
  isNeutral = false;
  byte flipState = 0;
  
  while(true)
  {
    if(digitalRead(buttonRed) == LOW)
    {
      red = true;
    }
    
    if(digitalRead(buttonBlue) == LOW)
    {
      blue = true;
    }
    
    if(blue && red)
    {
      isNeutral = true;
      allianceColor = strip.Color(255, 0, 255);
      
      for(i=0; i<strip.numPixels(); i+= 2)
      {
        strip.setPixelColor(i, 255, 0, 0);
        strip.setPixelColor(i+1, 0, 255, 0);
      }
      
      strip.show();
      
      fadeOut();
      
      return;
    }
    
    if(blue)
    {
      isBlue = true;
      allianceColor = strip.Color(0, 0, 255);
      
      setEntireStrip(0, 0, 255);
      
      fadeOut();
      
      return;
    }
    
    if(red)
    {
      isBlue = false;
      allianceColor = strip.Color(255, 0, 0);
      
      setEntireStrip(255, 0, 0);
      
      fadeOut();
      
      return;
    }
    
    if(millis() % (100*time) == 0)
    {
      flipState = bootloaderFlip(flipState);
    }
  }
}

byte bootloaderFlip(int flip)
{
  flip *= 3;
  setEntireStrip(0, 0, 0);
  for(i=flip; i<strip.numPixels(); i+=6)
  {
    strip.setPixelColor(i, 255, 0, 0);
    strip.setPixelColor(i+1, 255, 0, 0);
  }
  for(i=flip+3; i<strip.numPixels(); i+=6)
  {
    strip.setPixelColor(i, 0, 0, 255);
    strip.setPixelColor(i+1, 0, 0, 255);
  }
  flip /= 3;
  
  strip.show();
  return abs(flip-1);
}

void bootupAnimation2()
{
  boolean flashed[strip.numPixels()];
  byte pixelToFlash;
  byte lastPixelFlashed = 0;
  uint32_t colorToFlash;
  
  flashed[0] = true;
  
  for(i=1; i<strip.numPixels(); i++)
  {
    flashed[i] = false;
  }
  
  setEntireStrip(0, 0, 0);
  
  for(i=0; i<strip.numPixels(); i++)
  {
    pixelToFlash = random((strip.numPixels() - i));
    
    /*
    do
    {
      a = random(0, 200);
      b = random(0, 200);
      c = random(0, 200);
    } while(a+b+c > 150);
    */
    do
    {
      a = 50*random(2);
      b = 50*random(2);
      c = 50*random(2);
    } while(a+b+c == 0 || a+b+c == 150);
    
    colorToFlash = strip.Color(a, b, c);
    
    byte currentPixel = 0;
    
    for(j=0; j<pixelToFlash; j++)
    {
      do
      {
        currentPixel++;
      }
      while(flashed[currentPixel]);
      
    }
    
    strip.setPixelColor(currentPixel, 255, 255, 255);
    strip.setPixelColor(lastPixelFlashed, colorToFlash);
    strip.show();
    
    flashed[currentPixel] = true;
    lastPixelFlashed = currentPixel;
    
    //while(digitalRead(buttonRed) == HIGH);
    
    delay(20);
  }
  strip.setPixelColor(lastPixelFlashed, 0, 0, 0);
  
  delay(1000);
  
  fadeOut();
}

void sparkle(long time)
{
  byte intensity[strip.numPixels()];
  targetMillis = millis() + (1000*time);
  
  for(i=0; i<sizeof(intensity); i++)
  {
    intensity[i] = 0;
  }
  
  delay(10);
  
  do
  {
    if(true)
    {
      intensity[random(strip.numPixels())] = 255;
    }
    
    for(i=0; i<sizeof(intensity); i++)
    {
      if(intensity[i] > 4)
      {
        intensity[i] -= 4;
      }
      else
      {
        intensity[i] = 0;
      }
    }
    
    if(!isNeutral)
    {
      for(i=0; i<sizeof(intensity); i++)
      {
        if(isBlue)
        {
          strip.setPixelColor(i, 0, 0, intensity[i]);
        }
        else
        {
          strip.setPixelColor(i, intensity[i], 0, 0);
        }
      }
    }
    else
    {
      for(i=0; i<sizeof(intensity); i+= 2)
      {
        strip.setPixelColor(i, 0, intensity[i], 0);
        strip.setPixelColor(i+1, intensity[i], 0, 0);
      }
    }
    
    strip.show();
    
    delay(10);
  } while(millis() < targetMillis);
}

void flashFadeThroughWhite(long time)
{
  targetMillis = millis() + (1000 * time);
  
  byte pixelToFlash;
  byte lastPixelFlashed = 0;
  byte colors[125][3];
  boolean state = true;
  
  for(i=0; i<125; i++)
  {
    for(j=0; j<4; j++)
    {
      colors[i][j] = 0;
    }
  }
  
  delay(10);
  
  do
  {
    pixelToFlash = random(125);
    
    /*
    do
    {
      a = random(0, 200);
      b = random(0, 200);
      c = random(0, 200);
    } while(a+b+c > 150);
    */
    if(isNeutral)
    {
      do
      {
        if(random(3) == 1)
        {
          a = 100;
        }
        else
        {
          b = 100;
        }
      } while(a+b+c == 0 || a+b+c == 150);
    }
    else
    {
      if(isBlue)
      {
        a = random(50);
        b = random(50);
        c = 100;
      }
      else
      {
        a = 100;
        b = random(50);
        c = random(50);
      }
    }
    
    //colorToFlash = strip.Color(a, b, c);
    
    colors[lastPixelFlashed][1] = a;
    colors[lastPixelFlashed][2] = b;
    colors[lastPixelFlashed][3] = c;
    
    colors[pixelToFlash][1] = 255;
    colors[pixelToFlash][2] = 255;
    colors[pixelToFlash][3] = 255;
    
    lastPixelFlashed = pixelToFlash;

    for(i=0; i<125; i++)
    {
      for(j=0; j<4; j++)
      {
        if(colors[i][j] > 1)
        {
          colors[i][j] -= 1;
        }
        else
        {
          colors[i][j] = 0;
        }
      }
    }
    
    for(i=0; i<121; i++)
    {
      strip.setPixelColor(i, colors[i][1], colors[i][2], colors[i][3]);
    }
    
    strip.show();
    
    //while(digitalRead(buttonRed) == HIGH);
    
    delay(20);
  } while(millis() < targetMillis);
}

void insanity(long time)
{
  targetMillis = millis() + (1000 * time);
  
  do
  {
    for(i=0; i<strip.numPixels(); i++)
    {
      switch(random(3))
      {
        case 0: strip.setPixelColor(i, 0, 0, 0); break;
        case 1: strip.setPixelColor(i, 255, 0, 0); break;
        case 2: strip.setPixelColor(i, 0, 255, 0); break;
        case 3: strip.setPixelColor(i, 0, 0, 0); break;
        case 4: strip.setPixelColor(i, 0, 0, 0); break;
        case 5: strip.setPixelColor(i, allianceColor); break;
      }
    }
    strip.show();
    delay(random(70));
    setEntireStrip(0, 0, 0);
    delay(random(30));
  } while(millis() < targetMillis);
}

void insanityChase(long time)
{
  targetMillis = millis() + (1000 * time);
  
  int halfPix = strip.numPixels()/2;
  
  if(!isNeutral)
  {
    do
    {
      for(i=0; i<strip.numPixels(); i++)
      {
        strip.setPixelColor(i, 20, 20, 0);
      }
      
      j = millis()/time;
      j = j % 10;
      
      for(i=j; i<halfPix; i+= 10)
      {
        strip.setPixelColor(i, allianceColor);
        strip.setPixelColor(strip.numPixels() - i, allianceColor);
      }
      
      strip.show();
      
      delay(time);
    } while(millis() < targetMillis);
  }
  else
  {
    do
    {
      for(i=0; i<strip.numPixels(); i+= 2)
      {
        strip.setPixelColor(i, 40, 0, 0);
        strip.setPixelColor(i+1, 0, 40, 0);
      }
      
      j = millis()/time;
      j = j % 10;
      
      for(i=j; i<halfPix; i+= 10)
      {
        strip.setPixelColor(i, 255, 255, 255);
        strip.setPixelColor(strip.numPixels() - i, 255, 255, 255);
      }
      
      strip.show();
      
      delay(time);
    } while(millis() < targetMillis);
  }
}
/*
void offsetFlip(long time)
{
  targetMillis = millis() + (1000 * time);
  
  int offsets[strip.numPixels];
  
  for(i=0; i<strip.numPixels; i++)
  {
    offsets[i] = random(100);
  }
  
  while(millis() < targetMillis)
  {
    j = millis();
    j /= 5;
    j = j % 200;
    
    for(i=0; i<strip.numPixels; i++)
    {
      j += offset[i];
      j = j % 200;
      if(j <= 100)
      {
        strip.setPixelColor(i);
      }
    }
  }
}
*/
void setEntireStrip(int r, int g, int b)
{
  for(i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();
}

void fadeOut()
{
  for(i=brightness; i>0; i--)
  {
    strip.setBrightness(i);
    strip.show();
    delay(0);
  }
  
  setEntireStrip(0, 0, 0);
  
  strip.setBrightness(brightness);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

boolean testEscape()
{
  
}
