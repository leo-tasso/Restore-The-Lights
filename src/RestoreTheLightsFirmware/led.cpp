#include "WString.h"
#include "config.h"
#include <Arduino.h>
#include "utilities.h"

short int brightness = 0;
short int fadeAmount = 1;
short int activeLeds = 0;  //store the info about the led on/off
unsigned long timeBright = 0;

void updateLed() {
  for (int i = 0; i < BUTTON_NUM; i++) {
    if ((~activeLeds >> i) & 1) {
      digitalWrite(pinL[i], LOW);
    }
    if ((activeLeds >> i) & 1)
      digitalWrite(pinL[i], HIGH);
  }
}

//Returns the number of leds currently on
short int getActiveLedNum() {
  byte count = 0;
  for (int i = 0; i < 8; i++) {
    if (activeLeds & (1 << i)) {
      count++;
    }
  }
  return count;
}

//Turns on all leds
void turnOnAllLeds() {
  logger("All led On");
  activeLeds = 0b1111;
  updateLed();
}

//Truns off led identified by mask 1 2 4 8 in relative order
void turnOffLed(int ledMask) {
  activeLeds = activeLeds ^ ledMask;
  updateLed();
  logger("Turn off led");
  logger((String)activeLeds);
  logger((String)getActiveLedNum());
}

//Truns on led identified by mask 1 2 4 8 in relative order
void turnOnLed(int ledMask) {
  logger("Turn On led");
  activeLeds = activeLeds | ledMask;
  updateLed();
}

//Turn off all leds
void turnOffAllLeds() {
  logger("All led Off");
  activeLeds = 0b0000;
  updateLed();
}

//If called continuosly, make a led breath
void breathLed() {
  if (millis() > timeBright + BREATH_DELAY) {
    brightness += fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    analogWrite(LS, brightness);
    timeBright = millis();
  }
}

//Turn off red led (LS)
void turnOffLS() {
  digitalWrite(LS, LOW);
  brightness = 1;
}

//Turn on red led (LS)
void turnOnLS() {
  digitalWrite(LS, HIGH);
  brightness = 254;
}