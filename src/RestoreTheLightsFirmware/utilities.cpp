#include "WString.h"
#include <avr/sleep.h>
#include <stdlib.h>
#include <arduino.h>
#include <EnableInterrupt.h>
#include "utilities.h"
#include "config.h"
#include "led.h"

unsigned long entred_state_time;
unsigned long T1 = 0;
unsigned long T2 = T2_TIME_DEFAULT;
unsigned long T3 = T3_TIME_DEFAULT;
double F = 1;          //factor influencing T2 T3
unsigned short L = 0;  //difficulty level
volatile byte pressedButtons = 0;
game_state activeGameState = START_READY;
int sequence[BUTTON_NUM] = { 1, 2, 4, 8 };
unsigned long timePressed[BUTTON_NUM];
bool inputEnabled = 1;
void updateButton(int i);
#if BUTTON_NUM != 4
#pragma GCC error "Modify the handler array accordigly to your number of buttons"
#endif
void handler0(){updateButton(0);}
void handler1(){updateButton(1);}
void handler2(){updateButton(2);}
void handler3(){updateButton(3);}

void (*handler[BUTTON_NUM])(){handler0,handler1,handler2,handler3};
// To update the pressed mask every time any button is pressed or released, might split for each button
void updateButtons() {
  long time = millis();
  for (int i = 0; i < BUTTON_NUM; i++) {
  updateButton(i);
  }
  //logger((String)pressedButtons);
}

void updateButton(int i){
  long time = millis();
    if (time - timePressed[i] > BOUNCING_TIME) {
      timePressed[i] = time;
      int status = digitalRead(pinB[i]);
      if ((status ^ INVERTED) == HIGH) {
        //logger("Pressed");
        pressedButtons |= (0b1 << i);
      } else {
        pressedButtons &= ~(0b1 << i);
      }
    }
  //logger((String)pressedButtons);
}

void initializeInterrupts() {
  logger("Inizialized Interrupts");
  for (int i = 0; i < BUTTON_NUM; i++) {
    timePressed[i] = 0;
    enableInterrupt(pinB[i], handler[i], CHANGE);
  }
}

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
      break;

    case WAIT_START_TIME:
      logger("Wait Start Time");
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
  if (state == START_READY) Serial.println("Welcome to the Restore the light Game. Press key B1 to Start");
}



void StartReady() {
  if (millis() - entred_state_time < 10000) {
    L = map(analogRead(pot), 0, 1023, 1, 4);
    F = map(L, 1, 4, 1.2, 2.2);
    breathLed();
  } else {
    changeGameMode(SLEEP);
  }
  noInterrupts();
  if (pressedButtons == 1) {
    changeGameMode(WAIT_START_TIME);
  }
  interrupts();
}

void deepSleep() {
  logger("Entering Deep Sleep");
  turnOffBreather();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  changeGameMode(START_READY);
}

void waitStartTime() {
  if (T1 == 0) {
    T1 = random(MIN_WAIT_TIME, MAX_WAIT_TIME);
    generateSequence();
    turnOnAllLeds();
  }
  if (millis() - entred_state_time >= T1) {
    T1 = 0;
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
  if (!inputEnabled && !pressedButtons) inputEnabled = 1;
  if (inputEnabled) { //need to release all buttons before registering a new one
    if (millis() - entred_state_time > T3 || (pressedButtons != sequence[getActiveLedNum()] && pressedButtons != 0)) { //In case of overtime or wrong button pressed
      //TODO gameOver(); and score
      turnOffAllLeds(); //TODO maybe blink? check specifications
      Serial.println("Gamer Over");  //print also the score
      changeGameMode(START_READY);
    } else if (pressedButtons != 0) {
      inputEnabled = 0;
      if (getActiveLedNum() < BUTTON_NUM) {
        turnOnLed(sequence[getActiveLedNum()]);
      }
    }
  }
  if (getActiveLedNum() == BUTTON_NUM) {
    //TODO win
    Serial.println("WIN");
    changeGameMode(WAIT_START_TIME);
  }  //increase the score
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