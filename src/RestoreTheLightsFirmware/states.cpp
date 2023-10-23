/*
 * ASSIGNMENT #1 - RESTORE THE LIGHT  
 * 
 * Authors: L. Tassinari, M. Oliveri
 * 
 */
#include <avr/sleep.h>
#include <arduino.h>
#include "config.h"
#include "led.h"
#include "buttons.h"
#include "utilities.h"

unsigned long T1 = 0;
unsigned long T2 = T2_TIME_DEFAULT;
unsigned long T3 = T3_TIME_DEFAULT;
double F = 1;          //factor influencing T2 T3
unsigned short L = 0;  //difficulty level
bool inputEnabled = 1;
int sequence[BUTTON_NUM] = { 1, 2, 4, 8 };
unsigned long entred_state_time;
game_state activeGameState = START_READY;

void changeGameMode(game_state state) {
  activeGameState = state;
  entred_state_time = millis();
  switch (state) {
    case START_READY:
      logger("State Ready");
      Serial.println("Welcome to the Restore the light Game. Press key B1 to Start");
      break;

    case WAIT_START_TIME:
      logger("Wait Start Time");
      Serial.println("Go!");
      break;

    case DISPLAY_SEQUENCE:
      logger("Display Sequence");
      break;

    case USER_GAMEPLAY:
      logger("User Gameplay");
      break;

    case LOST:
      logger("Lost");
      break;

    case SLEEP:
      logger("Deep Sleep");
      break;
    default:
      break;
  }
}

void StartReady() {
  if (millis() - entred_state_time < 10000) {
    breathLed();
    logger((String)inputEnabled);
    byte momentaryPressedButtons = pressedButtons();
    if (momentaryPressedButtons == 1 && inputEnabled) {
      L = map(analogRead(pot), 0, 1024, 1, 5);
      F = map(L, 1, 4, 101, 140) / 100.0;
      logger("L:" + (String)L + " F:" + (String)F);
      T2 = T2_TIME_DEFAULT;
      T3 = T3_TIME_DEFAULT;
      changeGameMode(WAIT_START_TIME);
    } else if (momentaryPressedButtons == 0) {
      inputEnabled = 1;
    }
  } else {
    changeGameMode(SLEEP);
  }
}

void deepSleep() {
  inputEnabled = 0;  //If woken a button has been pressed
  logger("Entering Deep Sleep");
  turnOffLS();
  delay(50);  //Delay to allow actions before sleep
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  changeGameMode(START_READY);
}

void waitStartTime() {
  turnOffLS();
  if (T1 == 0) {
    T1 = random(MIN_WAIT_TIME, MAX_WAIT_TIME);
    logger((String)T1 + "T1");
    generateSequence(sequence);
    turnOffAllLeds();
  }
  if (millis() - entred_state_time >= T1) {
    T1 = 0;
    turnOnAllLeds();
    changeGameMode(DISPLAY_SEQUENCE);
    T2 = T2 / F;
    T3 = T3 / F;
    logger((String)T2 + (String)T3);
  }
}

void displaySequence() {
  if (getActiveLedNum() == 0) {
    logger((String)T2 + "T2");
    logger((String)(getActiveLedNum()));
    changeGameMode(USER_GAMEPLAY);
  } else if (millis() - entred_state_time > T2 / BUTTON_NUM) {
    turnOffLed(sequence[getActiveLedNum() - 1]);
    entred_state_time = millis();  //Update entered state time
  }
}

void userGameplay() {
  byte momentaryPressedButtons = pressedButtons();
  if (!inputEnabled && !momentaryPressedButtons) inputEnabled = 1;
  if (inputEnabled && momentaryPressedButtons != 0) {  //need to release all buttons before registering a new one
    //In case of overtime or wrong button pressed
    if (millis() - entred_state_time > T3 || (momentaryPressedButtons != sequence[getActiveLedNum()])) {
      gameOver();
      inputEnabled = !momentaryPressedButtons;  // Set inputEnabled, if no pressed buttons, it's enabled
    } else if (getActiveLedNum() < BUTTON_NUM) {
      turnOnLed(sequence[getActiveLedNum()]);
    }
    inputEnabled = 0;
  }
  if (getActiveLedNum() == BUTTON_NUM) {
    win(T2_TIME_DEFAULT - T2);
  }
}

void lost() {
  if (millis() - entred_state_time >= 2000)
    changeGameMode(START_READY);
}

void victoryCooldown() {
  if (millis() - entred_state_time >= (3 * BLINK_TIME))
    changeGameMode(WAIT_START_TIME);
  else if (millis() - entred_state_time >= (2 * BLINK_TIME))
    turnOnAllLeds();
  else if (millis() - entred_state_time >= BLINK_TIME)
    turnOffAllLeds();
}

game_state getActiveGameMode() {
  return activeGameState;
}