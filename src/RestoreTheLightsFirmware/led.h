#ifndef LED
#define LED

short int getActiveLedNum();    //Returns the number of leds currently on

void turnOnAllLeds();           //Turns on all leds

void turnOffLed(int ledMask);   //Truns off led identified by mask 8 4 2 1 in relative order

void turnOnLed(int ledMask);    //Truns on led identified by mask 8 4 2 1 in relative order
#endif