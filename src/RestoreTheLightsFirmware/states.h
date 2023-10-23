/*
 * ASSIGNMENT #1 - RESTORE THE LIGHT  
 * 
 * Authors: L. Tassinari, M. Oliveri
 * 
 */
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