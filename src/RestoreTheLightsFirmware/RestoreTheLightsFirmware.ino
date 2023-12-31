/*
 * ASSIGNMENT #1 - RESTORE THE LIGHT  
 * 
 * Authors: L. Tassinari, M. Oliveri
 * 
 */
#include <stdlib.h>
#include "config.h"
#include "utilities.h"
#include "buttons.h"
#include "states.h"

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
  updateButtons();  //check also every cycle for button pressed in case of false positive
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

    case LOST:
      lost();
      break;

    case VICTORY_COOLDOWN:
      victoryCooldown();
      break;

    case SLEEP:
      deepSleep();
      break;
  }
}