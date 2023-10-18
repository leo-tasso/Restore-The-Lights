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

void changeGameMode(game_state state);

game_state getActiveGameMode();

#endif