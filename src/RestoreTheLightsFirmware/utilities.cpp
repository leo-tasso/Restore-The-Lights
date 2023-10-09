#include "config.h"
#include <avr/sleep.h>
#include <EnableInterrupt.h>
#include <stdlib.h>

short int brightness = 0;
short int fadeAmount = 5;
unsigned long entred_state_time;
unsigned long T1 = 0;
int ledsOn =COLUMNS;
game_state activeGameState = WAIT_START;
int sequence[COLUMNS] = {1,2,4,8};



void waitStart() {
    entred_state_time = millis();
    enableInterrupt(pinB[1],startGame,CHANGE);
    Serial.println("Welcome to the Restore the light Game. Press key B1 to Start");
    while (millis()-entred_state_time < 10000) {
        analogWrite(LS,brightness);
        brightness += fadeAmount;
        if (brightness == 0 || brightness == 255) fadeAmount = -fadeAmount;
  }
  deepSleep();
}

 void game() {

 }

 void deepSleep() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
    sleep_enable();
    sleep_mode();
    sleep_disable(); 
    waitStart();
 }

 void startGame(){
  disableInterrupt(pinB[1]);
  game();
}

void waitTime(){
    if(T1==0){
        T1=rand()% MAX_WAIT_TIME;
        generateSequence();
        //TODO turn on all leds
        ledsOn=COLUMNS;
    }
    if(millis()-entred_state_time>=T1){
        T1=0;
        changeGameMode(DISPLAY_SEQUENCE);
    }
}

void displaySequence(){
    if(ledsOn==0){
        changeGameMode(USER_GAMEPLAY);
    }
    else if(entred_state_time-millis()<T2/ledsOn){
        //TODO turn off first led
        ledsOn--;
    }
}

void userGameplay(){
    if(entred_state_time-millis()>T3 || (pressedButtons!=sequence[ledsOn]&&pressedButtons!=0)){
        gameOver();
    }else if(ledsOn<COLUMNS){
        //TODO turn on first led sequence
        ledsOn++;
    }else{
        //TODO win
        changeGameMode(WAIT_START);
    }
    void changeGameMode(game_state state){
        activeGameState = state;
        entred_state_time = millis();
    }

    void generateSequence(){
        for (int i = COLUMNS - 1; i > 0; i--) {
            int j = random(0, i + 1);
            // Swap array[i] and array[j]
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}