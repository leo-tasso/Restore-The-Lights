#include "WString.h"
#include "config.h"
#include <Arduino.h>
#include "utilities.h"

short int brightness = 0;
short int fadeAmount = 1;
short int activeLeds = 0;  //store the info about the led on/off
unsigned long timeBright = 0;

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
  for (int i = 0; i < BUTTON_NUM; i++) {
    digitalWrite(pinL[i], HIGH);
  }
  activeLeds = 0b1111;
}

//Truns off led identified by mask 1 2 4 8 in relative order
void turnOffLed(int ledMask) {
  activeLeds = activeLeds ^ ledMask;
  for (int i = 0; i < BUTTON_NUM; i++) {
    if ((ledMask >> i) & 1) {
      digitalWrite(pinL[i], LOW);
    }
  }
  logger("Turn off led");
  logger((String)activeLeds);
  logger((String)getActiveLedNum());
}

//Truns on led identified by mask 1 2 4 8 in relative order
void turnOnLed(int ledMask) {
  logger("Turn On led");
  activeLeds = activeLeds | ledMask;
  for (int i = 0; i < BUTTON_NUM; i++) {
    if ((activeLeds >> i) & 1)
      digitalWrite(pinL[i], HIGH);
  }
}

//Turn off all leds
void turnOffAllLeds(){
  logger("All led Off");
  for (int i = 0; i < BUTTON_NUM; i++) {
    digitalWrite(pinL[i], LOW);
  }
  activeLeds = 0b0000;
}

//If called continuosly, make a led breath
void breathLed() {
  analogWrite(LS, brightness);
  if(millis() > timeBright + BREATH_DELAY){
    brightness += fadeAmount;
    timeBright = millis();
  }
  if (brightness <= 1 || brightness >= 255) fadeAmount = -fadeAmount;
}

//Turn off red led (LS)
void turnOffLS(){
  analogWrite(LS,LOW);
}

//Turn on red led (LS)
void turnOnLS() {
  analogWrite(LS,HIGH);
}