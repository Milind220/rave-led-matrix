#include <Arduino.h>
#include "config.h"
#include "twinklefox.h"
#include "pride.h"

#define BUTTON_PIN 8
#define FREQUENCY_PIN A0
#define COLOR_PIN A3

#define DEBOUNCE_DELAY 100UL
#define NUM_MODES 3

unsigned long lastDebounceTime = 0UL;
uint8_t mode = 0;
uint16_t frequency = 0;
uint16_t color = 0;

void setup() {
  Serial.begin(9600);
  delay(3000); //safety startup delay
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_MA);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip);
  
  pinMode(BUTTON_PIN, INPUT);

  // Setup for specific animations
  twinklefoxSetup();
}

void loop() {
  // Debounce and read button
  if (millis() - lastDebounceTime > DEBOUNCE_DELAY) {
    if (digitalRead(BUTTON_PIN) == HIGH) {
      mode++;
      if (mode >= NUM_MODES) {
        mode = 0;
      }
    }
    lastDebounceTime = millis();
  }

  // Read the frequency and the colour
  frequency = analogRead(FREQUENCY_PIN);
  delay(10);
  color = analogRead(COLOR_PIN);

  // Run the animation
  switch (mode) {
    case 0:
      twinklefoxLoop(frequency, color);
      break;
    case 1:
      prideLoop();
      break;
    case 2:
      break;
  }
  Serial.print("mode: ");
  Serial.print(mode);
  Serial.print(" | frequency: ");
  Serial.print(frequency);
  Serial.print(" | color: ");
  Serial.println(color);
}