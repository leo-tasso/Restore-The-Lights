#ifndef UTILITIES
#define UTILITIES

#include "config.h"

void waitStart();

void game(float T2, float T3);

void deepSleep();

void displaySequence();

void userGameplay();

short int getActiveLedNum();

void turnOnAllLeds();

void turnOffLed(int ledMask); //Truns off led identified by mask 8 4 2 1 in relative order

game_state getActiveGameMode();

void changeGameMode(game_state state);


void generateSequence();

#endif