#ifndef UTILITIES
#define UTILITIES

#include "config.h"

void StartReady();

void waitStartTime();

void deepSleep();

void displaySequence();

void userGameplay();

game_state getActiveGameMode();

void changeGameMode(game_state state);


void generateSequence();

void initializeInterrupts();

#endif