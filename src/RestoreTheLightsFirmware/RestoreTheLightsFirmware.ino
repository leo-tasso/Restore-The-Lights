#include <avr/sleep.h>
#include <EnableInterrupt.h>
#include <stdlib.h>
#include "utilities.h"

void setup(){
    //Setup pins
    srand(millis()%100);
    pinMode(pot,INPUT);
    pinMode(LS, OUTPUT);
    for(int i=0; i<COLUMNS; i++){
        pinMode(pinL[i],OUTPUT);
        pinMode(pinB[i],INPUT_PULLUP);
    }
    Serial.begin(9600);
    waitStart(); //Entry point, the first state
}

void loop() {
    
    switch (game_state)
    {
    case WAIT_START:
        waitStart();
        break;

    case WAIT_START_TIME:
        break;

    case DISPLAY_SEQUENCE:
        displaySequence();
        break;

    case USER_GAMEPLAY:
        userGameplay();
        break;

    case SLEEP:
        deepSleep();
        break;
    
}