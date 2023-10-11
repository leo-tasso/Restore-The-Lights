#include "config.h"
#include <Arduino.h>


short int brightness = 0;
short int fadeAmount = 5;

//Returns the number of leds currently on
short int getActiveLedNum(){}

//Turns on all leds
void turnOnAllLeds(){}

//Truns off led identified by mask 1 2 4 8 in relative order
void turnOffLed(int ledMask){}

//Truns on led identified by mask 1 2 4 8 in relative order
void turnOnLed(int ledMask){}

//if called continuosly, make a led breath
void breathLed(int led){
    analogWrite(LS, brightness);
    brightness += fadeAmount;
    if (brightness == 0 || brightness == 255) fadeAmount = -fadeAmount;
}