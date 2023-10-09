#include <stdlib.h>
#include "config.h"
#include "utilities.h"

extern game_state activeGameState;

void setup(){
    srand(millis()%100); //seed of rand function
    //Setup pins
    pinMode(pot,INPUT);
    pinMode(LS, OUTPUT);
    for(int i=0; i<COLUMNS; i++){
        pinMode(pinL[i],OUTPUT);
        pinMode(pinB[i],INPUT_PULLUP);
    }
    Serial.begin(9600);
    changeGameMode(WAIT_START); //Entry point, the first state
}

void loop() {
    
    switch (activeGameState){
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