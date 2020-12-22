#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 16
#define LED_PIN 3

#define debug false

byte gammatable[256];

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB+NEO_KHZ800);

void setup() {
  if(debug){
    Serial.begin(115200);
  }
  tcs.begin();
  pixels.begin();
  for (int i = 0; i < 256; i++){
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
    gammatable[i] = x;
  }
}

void loop(){
  float r, g, b;
  delay(60);
  tcs.getRGB(&r, &g, &b);
  if(debug){
    Serial.print("R: "); 
    Serial.print(int(r)); 
    Serial.print("\tG: "); 
    Serial.print(int(g)); 
    Serial.print("\tB: "); 
    Serial.println(int(b));
  }
  for(int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(gammatable[(int)r], gammatable[(int)g], gammatable[(int)b]));
  }
  pixels.show();
}
