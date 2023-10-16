#include "WString.h"
#include <avr/sleep.h>
#include <stdlib.h>
#include <arduino.h>
#include "utilities.h"
#include "config.h"
#include "led.h"
#include "buttons.h"

unsigned long entred_state_time;
unsigned long T1 = 0;
unsigned long T2 = T2_TIME_DEFAULT;
unsigned long T3 = T3_TIME_DEFAULT;
double F = 1;          //factor influencing T2 T3
unsigned short L = 0;  //difficulty level
unsigned short score = 0;
game_state activeGameState = START_READY;
int sequence[BUTTON_NUM] = { 1, 2, 4, 8 };
bool inputEnabled = 1;

void generateSequence() {
  for (int i = BUTTON_NUM - 1; i > 0; i--) {
    int j = random(0, i + 1);
    int temp = sequence[i];
    sequence[i] = sequence[j];
    sequence[j] = temp;
  }
}

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
      logger((String)sequence[0] + (String)sequence[1] + (String)sequence[2] + (String)sequence[3]);
      break;

    case SLEEP:
      logger("Deep Sleep");
      break;
  }
}

void gameOver() {
  turnOffAllLeds();
  Serial.print("Gamer Over. Final score: ");
  Serial.println(score);
  score = 0;
  turnOnLS();
  delay(1000); //inutile se gli interrupt sono abilitati
  changeGameMode(START_READY);
}

void win() {
  score += 10;
  Serial.print("New point! Score");
  Serial.println(score);
  changeGameMode(WAIT_START_TIME);
}


void StartReady() {
  if (millis() - entred_state_time < 10000) {
    L = map(analogRead(pot), 0, 1023, 1, 4);
    F = map(L, 1, 4, 1.1, 1.6);
    breathLed();
    noInterrupts();
    if (pressedButtons() == 1 && inputEnabled) {
      changeGameMode(WAIT_START_TIME);
    }
    else if(pressedButtons()==0){
      inputEnabled = 1;
    }
    interrupts();
  } else {
    changeGameMode(SLEEP);
  }
}

void deepSleep() {
  logger("Entering Deep Sleep");
  turnOffLS();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  inputEnabled=false; //If woken a button has been pressed
  changeGameMode(START_READY);
}

void waitStartTime() {
  turnOffLS();
  if (T1 == 0) {
    T1 = random(MIN_WAIT_TIME, MAX_WAIT_TIME);
    generateSequence();
    turnOffAllLeds();
  }
  if (millis() - entred_state_time >= T1) {
    T1 = 0;
    turnOnAllLeds();
    changeGameMode(DISPLAY_SEQUENCE);
    T2 = T2 / F;
    T3 = T3 / F;
  }
}

void displaySequence() {
  if (getActiveLedNum() == 0) {
    logger((String)T2);
    logger((String)(getActiveLedNum()));
    changeGameMode(USER_GAMEPLAY);
  } else if (millis() - entred_state_time > T2 / BUTTON_NUM) {
    turnOffLed(sequence[getActiveLedNum() - 1]);
    entred_state_time = millis();  //Update entered state time
  }
}

void userGameplay() {
  noInterrupts();
  if (!inputEnabled && !pressedButtons()) inputEnabled = 1;
  if (inputEnabled) { //need to release all buttons before registering a new one
    if (millis() - entred_state_time > T3 || (pressedButtons() != sequence[getActiveLedNum()] && pressedButtons != 0)) { //In case of overtime or wrong button pressed
      gameOver();
      inputEnabled = !pressedButtons(); // Set inputEnabled, if no pressed buttons, it's enabled
    } else if (pressedButtons() != 0) {
      inputEnabled = 0;
      if (getActiveLedNum() < BUTTON_NUM) {
        turnOnLed(sequence[getActiveLedNum()]);
      }
    }
  }
  if (getActiveLedNum() == BUTTON_NUM) {
    win();
  }
  interrupts();
}

game_state getActiveGameMode() {
  return activeGameState;
}

void logger(String s) {
#ifdef DEBUG
  Serial.println(s);
#endif
}