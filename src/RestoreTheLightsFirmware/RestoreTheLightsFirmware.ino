#include <stdlib.h>
#include "config.h"
#include "utilities.h"


void setup() {
  randomSeed(analogRead(0));  //seed of rand function
  //Setup pins
  pinMode(pot, INPUT);
  pinMode(LS, OUTPUT);
  for (int i = 0; i < BUTTON_NUM; i++) {
    pinMode(pinL[i], OUTPUT);
    pinMode(pinB[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
  initializeInterrupts();
  changeGameMode(START_READY);  //Entry point, the first state
}

void loop() {

  switch (getActiveGameMode()) {
    case START_READY:
      StartReady();
      break;

    case WAIT_START_TIME:
      waitStartTime();
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