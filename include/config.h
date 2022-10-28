#ifndef CONFIG_H
#define CONFIG_H

#include <FastLED.h>

#define NUM_LEDS 15 
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define DATA_PIN 9 
#define VOLTS 4.5 
#define MAX_MA 200
#define BRIGHTNESS 75

extern CRGBArray<NUM_LEDS> leds;

#endif // CONFIG_H