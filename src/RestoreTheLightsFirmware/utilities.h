#ifndef UTILITIES
#define UTILITIES

#include "config.h"

void waitStart();

void game(float T2, float T3);

void deepSleep();

void displaySequence();

void userGameplay();

game_state getActiveGameMode();

void changeGameMode(game_state state);


void generateSequence();

void initializeInterrupts();

#endif