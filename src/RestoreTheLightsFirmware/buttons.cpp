#include "config.h"
#include <arduino.h>
#include <EnableInterrupt.h>
#include "utilities.h"
volatile byte pressedButtonsBuffer = 0;
unsigned long timePressed[BUTTON_NUM];
void updateButton(int i);

#if BUTTON_NUM != 4
#pragma GCC error "Modify the handler array accordigly to your number of buttons"
#endif
void handler0() {
  updateButton(0);
}
void handler1() {
  updateButton(1);
}
void handler2() {
  updateButton(2);
}
void handler3() {
  updateButton(3);
}

void (*handler[BUTTON_NUM])(){ handler0, handler1, handler2, handler3 };

// To update the pressed mask every time any button is pressed or released, might split for each button
void updateButtons() {
  noInterrupts();
  for (int i = 0; i < BUTTON_NUM; i++) {
    updateButton(i);
  }
  interrupts();
}

void updateButton(int i) {
  long time = millis();
  if (time - timePressed[i] > BOUNCING_TIME) {
    timePressed[i] = time;
    int status = digitalRead(pinB[i]);
    if ((status ^ INVERTED) == HIGH) {
      //logger("Pressed");
      pressedButtonsBuffer |= (0b1 << i);
    } else {
      pressedButtonsBuffer &= ~(0b1 << i);
    }
  }
  //logger((String)pressedButtonsBuffer);
}

void initializeInterrupts() {
  logger("Inizialized Interrupts");
  for (int i = 0; i < BUTTON_NUM; i++) {
    timePressed[i] = 0;
    enableInterrupt(pinB[i], handler[i], CHANGE);
  }
}

byte pressedButtons() {
  noInterrupts();
  byte buttons = pressedButtonsBuffer;
  interrupts();
  return buttons;
}
