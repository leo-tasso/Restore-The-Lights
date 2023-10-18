#ifndef UTILITIES
#define UTILITIES

#include "config.h"

void StartReady();

void waitStartTime();

void deepSleep();

void displaySequence();

void userGameplay();

void lost();

void victoryCooldown();

game_state getActiveGameMode();

void changeGameMode(game_state state);

void initializeInterrupts();

void logger(String s);

void updateButtons();

#endif