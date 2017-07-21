#include <Arduino.h>

//FastLED_AnalogueInput.ino

/*
   Using a potentiometer to control colour, brightness and speed.
 Wire up as per http://arduino.cc/en/Tutorial/AnalogInput
 You can connect the wiper, to any analogue input pin, and
 adjust the settings below.
 You will need three 10k potentiometers.
 */


#include <FastLED.h>


#define LED_PIN 4            // which pin are LEDS connected to?
#define NUM_LEDS 60
#define COLOR_ORDER GRB
#define LED_TYPE WS2812        // i'm using WS2811s, FastLED supports lots of different types.

/*
 set your desired minimum and maxium brigtness settings here.
 Valid values are 0 - 255
 With 0 being fully dim, or not lit, and 255 being fully on.
 Therefore half power, or 50%, would be 128
 */

#define MAX_BRIGHTNESS 255     // Thats full on, watch the power!
#define MIN_BRIGHTNESS 0       // set to a minimum of 25%

const int brightnessInPin = A1;  // The Analog input pin that the brightness control potentiometer is attached to.
const int colourInPin = A3;      // The Analog input pin that the colour control potentiometer is attached to.
int mappedHue = 0;
int mappedValue = 0;

long sumHue = 0;
long sumValue = 0;

int averageHue = 32;
int averageValue =32;

int samplePeriod = 300 ;

int old_poten;
int hue_old_poten;

int lastHue;
int lastValue;

int counter = 0;

struct CRGB leds[NUM_LEDS];

void setup() {
  delay(2000); // in case we do something stupid. We dont want to get locked out.

  LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  // FastLED.setBrightness(MAX_BRIGHTNESS);

  LEDS.showColor(CRGB(255, 0, 0));
  delay(500);
  LEDS.showColor(CRGB(0, 255, 0));
  delay(500);
  LEDS.showColor(CRGB(0, 0, 255));
  delay(500);
  LEDS.showColor(CRGB(0, 0, 0));


}

void loop() {

  // if (millis()%samplePeriod==0){
  // averageHue = sumHue / counter;
  // averageValue = sumValue / counter;
  //
  // // if (lastValue != averageValue){

  // LEDS.showColor(CRGB(0, 0, 0));

//   // }
// }
// else{
  // int mappedHue = map(analogRead(brightnessInPin), 0, 1023, 0, 255);
  // int mappedValue = map(analogRead(colourInPin), 0, 1023, 0, 255);
//   sumHue+=mappedHue;
//   sumValue+=mappedValue;
//
// }
// counter++;
// lastHue = averageHue;

int poten = map(analogRead(brightnessInPin), 0, 1023, 0, 255);
if (abs(poten - old_poten)> 10){
 old_poten = poten;  // save the changed value
 FastLED.setBrightness(constrain(poten, MIN_BRIGHTNESS, MAX_BRIGHTNESS));
 LEDS.showColor(CRGB(255, 255, 255));
 delay(10);
}



int hue_poten = map(analogRead(colourInPin), 0, 1023, 0, 255);
if (abs(hue_poten - hue_old_poten)> 10){
 hue_old_poten = hue_poten;  // save the changed value
 FastLED.setBrightness(constrain(poten, MIN_BRIGHTNESS, MAX_BRIGHTNESS));
 LEDS.showColor(CRGB(hue_poten, 255, 255));
 delay(10);
}

}
