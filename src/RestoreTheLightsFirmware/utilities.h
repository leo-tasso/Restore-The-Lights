/*
 * ASSIGNMENT #1 - RESTORE THE LIGHT  
 * 
 * Authors: L. Tassinari, M. Oliveri
 * 
 */
#ifndef STATES
#define STATES
#include "config.h"


void initializeInterrupts();

void logger(String s);

void updateButtons();

void generateSequence(int* sequence);

void win(int pointIncrease);

void gameOver();

#endif