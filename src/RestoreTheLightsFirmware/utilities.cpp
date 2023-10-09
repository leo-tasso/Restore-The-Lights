#include "config.h"
#include <avr/sleep.h>
#include <stdlib.h>
#include <arduino.h>
#include "utilities.h"
#include <EnableInterrupt.h>
#include "led.h"

short int brightness = 0;
short int fadeAmount = 5;
unsigned long entred_state_time;
unsigned long T1 = 0;
unsigned long T2 = 0;
unsigned long T3 = 0;
byte pressedButtons = 0;
game_state activeGameState = WAIT_START;
int sequence[BUTTON_NUM] = { 1, 2, 4, 8 };
unsigned long timePressed[BUTTON_NUM];

// To update the pressed mask every time any button is pressed or released, might split for each button
void updateButtons() {
  long time = millis();
  for (int i = 0; i < BUTTON_NUM; i++) {
    if (time - timePressed[i] > BOUNCING_TIME) {
      timePressed[i] = time;
      int status = digitalRead(pinB[i]);
      if (status == HIGH) {
        if (!(pressedButtons & (0b1 << i))) {
            pressedButtons |= (0b1 << i);
        } else {
          pressedButtons &= ~(1 << i);
        }
      }
    }
  }
}




void initializeInterrupts() {
  for (int i = 0; i < BUTTON_NUM; i++) {
    timePressed[i] = 0;
    enableInterrupt(digitalPinToInterrupt(pinL[i]), updateButtons, CHANGE);
  }
}





void waitStart() {//TODO include potentiomenter and use pressed buttons instead of interrupts
  entred_state_time = millis();
  //enableInterrupt(pinB[1],startGame,CHANGE);
  Serial.println("Welcome to the Restore the light Game. Press key B1 to Start");
  while (millis() - entred_state_time < 10000) {
    analogWrite(LS, brightness);
    brightness += fadeAmount;
    if (brightness == 0 || brightness == 255) fadeAmount = -fadeAmount;
  }
  deepSleep();
}

void deepSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  waitStart();
}


void waitTime() {
  if (T1 == 0) {
    T1 = rand() % MAX_WAIT_TIME;
    generateSequence();
    turnOnAllLeds();
  }
  if (millis() - entred_state_time >= T1) {
    T1 = 0;
    changeGameMode(DISPLAY_SEQUENCE);
  }
}

void displaySequence() {
  if (getActiveLedNum() == 0) {
    changeGameMode(USER_GAMEPLAY);
  } else if (entred_state_time - millis() < T2 / getActiveLedNum()) {
    turnOffLed(sequence[getActiveLedNum() -1]);
  }
}

void userGameplay() {
  if (entred_state_time - millis() > T3 || (pressedButtons != sequence[getActiveLedNum()] && pressedButtons != 0)) {
    //TODO gameOver();
  } else if (getActiveLedNum() < BUTTON_NUM) {
    turnOnLed(sequence[getActiveLedNum()]);
  } else {
    //TODO win
    changeGameMode(WAIT_START);
  }
}

game_state getActiveGameMode() {
  return activeGameState;
}


void changeGameMode(game_state state) {
  activeGameState = state;
  entred_state_time = millis();
}

void generateSequence() {
  for (int i = BUTTON_NUM - 1; i > 0; i--) {
    int j = random(0, i + 1);
    int temp = sequence[i];
    sequence[i] = sequence[j];
    sequence[j] = temp;
  }
}