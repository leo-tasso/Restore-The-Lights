#include <avr/sleep.h>
#include <avr/power.h>
#include "config.h"
#include "interruptAll.h"


void waitStart();

void game(float T2, float T3);

void deepSleep();

void setup(){
    //Setup pins
    pinMode(pot,INPUT);
    pinMode(LS, OUTPUT);
    for(int i=0; i<COLUMNS; i++){
        pinMode(pinL[i],OUTPUT);
        pinMode(pinB[i],INPUT_PULLUP);
    }
    waitStart(); //Entry point, the first state
}

void loop() {
    deepSleep(); //In case Superloop is reached (it shouldn't) goes back to deepSleep state
}

void waitStart() {

}

 void game() {

 }

 void deepSleep() {
    allButtonsAttachIntterrupt(wakeFromSleep);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
    sleep_enable();
    sleep_mode(); 
 }

void wakeFromSleep(){
    sleep_disable(); 
    allButtonsDetatchIntterrupt();
    waitStart();
 }