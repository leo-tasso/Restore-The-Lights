/*
 * ASSIGNMENT #1 - RESTORE THE LIGHT  
 * 
 * Authors: L. Tassinari, M. Oliveri
 * 
 */
#ifndef LED
#define LED

short int getActiveLedNum();    //Returns the number of leds currently on

void turnOnAllLeds();           //Turns on all leds

void turnOffLed(int ledMask);   //Truns off led identified by mask 1 2 4 8 in relative order

void turnOnLed(int ledMask);    //Truns on led identified by mask 1 2 4 8 in relative order

void breathLed();               //If called continuosly, make a led breath

void turnOffLS();               //Switches off the breathing led

void turnOnLS();                //Switches on the red led

void turnOffAllLeds();          //Turns off all the game leds

#endif