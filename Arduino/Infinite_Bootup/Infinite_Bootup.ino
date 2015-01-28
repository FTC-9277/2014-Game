#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(120, 9, NEO_GRB + NEO_KHZ800);
int i, j, a, b, c;
boolean state;

byte pixelToFlash;
byte lastPixelFlashed = 0;
byte colors[125][3];
uint32_t colorToFlash;

void setup()
{
  lastPixelFlashed = 0;
  pinMode(9, OUTPUT);
  pinMode(4, INPUT_PULLUP);
  
  for(i=0; i<125; i++)
  {
    for(j=0; j<4; j++)
    {
      colors[i][j] = 0;
    }
  }
}

void loop()
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
  do
  {
    a = 50*random(2);
    b = 50*random(2);
    c = 50*random(2);
  } while(a+b+c == 0 || a+b+c == 150);
  
  //colorToFlash = strip.Color(a, b, c);
  if(digitalRead(4) == HIGH)
  {
    colors[lastPixelFlashed][1] = a;
    colors[lastPixelFlashed][2] = b;
    colors[lastPixelFlashed][3] = c;
    
    colors[pixelToFlash][1] = 255;
    colors[pixelToFlash][2] = 255;
    colors[pixelToFlash][3] = 255;
  }
  
  lastPixelFlashed = pixelToFlash;
  
  if(state)
  {
    for(i=0; i<125; i++)
    {
      for(j=0; j<4; j++)
      {
        if(colors[i][j] > 1)
        {
          colors[i][j] -= 0.1;
        }
        else
        {
          colors[i][j] = 0;
        }
      }
    }
  }
  
  for(i=0; i<121; i++)
  {
    strip.setPixelColor(i, colors[i][1], colors[i][2], colors[i][3]);
  }
  
  strip.show();
  
  state = !state;
  
  //while(digitalRead(buttonRed) == HIGH);
  
  delay(20);
}
