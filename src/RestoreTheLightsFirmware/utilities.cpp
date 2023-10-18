#include <arduino.h>
#include "utilities.h"
#include "config.h"
#include "led.h"
#include "buttons.h"
#include "states.h"

unsigned short score = 0;

void logger(String s) {
#ifdef DEBUG
  Serial.println(s);
#endif
}

void generateSequence(int* sequence) {
  for (int i = BUTTON_NUM - 1; i > 0; i--) {
    int j = random(0, i + 1);
    int temp = sequence[i];
    sequence[i] = sequence[j];
    sequence[j] = temp;
  }
}

void gameOver() {
  turnOffAllLeds();
  Serial.print("Gamer Over. Final score: " + String(score));
  score = 0;
  turnOnLS();
  changeGameMode(LOST);
}

void win() {
  score += 10;
  Serial.print("New point! Score" + String(score));
  changeGameMode(VICTORY_COOLDOWN);
}
