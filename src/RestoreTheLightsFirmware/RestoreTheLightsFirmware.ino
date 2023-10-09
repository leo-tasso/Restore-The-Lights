#include <stdlib.h>
#include "config.h"
#include "utilities.h"


void setup(){
    srand(millis()%100); //seed of rand function
    //Setup pins
    pinMode(pot,INPUT);
    pinMode(LS, OUTPUT);
    for(int i=0; i<BUTTON_NUM; i++){
        pinMode(pinL[i],OUTPUT);
        pinMode(pinB[i],INPUT_PULLUP);
    }
    //TODO Attach interrupts to buttons
    Serial.begin(9600);
    initializeInterrupts();
    changeGameMode(WAIT_START); //Entry point, the first state
}

void loop() {
    
    switch (getActiveGameMode()){
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
}