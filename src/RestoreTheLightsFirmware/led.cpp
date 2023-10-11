#include "config.h"
#include <Arduino.h>


short int brightness = 0;
short int fadeAmount = 5;
short int mask = 0b0000; //store the info about the led on/off

//Returns the number of leds currently on
short int getActiveLedNum(){
    return mask;
}

//Turns on all leds
void turnOnAllLeds(){
    for(int i = 0; i < BUTTON_NUM; i++){
        digitalWrite(pinL,HIGH);
    }
    mask = 0b1111;
}

//Truns off led identified by mask 1 2 4 8 in relative order
void turnOffLed(int ledMask){
    mask = mask ^ ledMask; //error in case try to turn off a led already off
    for( int i = 0; i < BUTTON_NUM; i++){
        if( (ledMask >> i) & 1) {
            digitalWrite(pinL[BUTTON_NUM-i], LOW);
        }
    }
}

//Truns on led identified by mask 1 2 4 8 in relative order
void turnOnLed(int ledMask){
    mask = mask | ledMask;
    for( int i = 0; i < BUTTON_NUM; i++){
        if( (mask >> i) & 1)
            digitalWrite(pinL[BUTTON_NUM-i], HIGH);
    }
}

//if called continuosly, make a led breath
void breathLed(int led){
    analogWrite(LS, brightness);
    brightness += fadeAmount;
    if (brightness == 0 || brightness == 255) fadeAmount = -fadeAmount;
}