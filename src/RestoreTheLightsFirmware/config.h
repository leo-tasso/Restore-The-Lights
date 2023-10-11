#ifndef CONFIG
#define CONFIG
#define pot A0      //Pin of potentiometer
#define LS 13       //Pin of status LED, must be PWM pin
#define BUTTON_NUM 4   //The number of pairs led-button
#define MAX_WAIT_TIME 1000
#define MIN_WAIT_TIME 1
#define T1_TIME_DEFAULT 1500
#define T2_TIME_DEFAULT 2500
#define BOUNCING_TIME 5 //ms
enum game_state {START_READY, WAIT_START_TIME, DISPLAY_SEQUENCE, USER_GAMEPLAY, SLEEP};
const unsigned short pinL[BUTTON_NUM] = {6,7,8,9} ;
const unsigned short pinB[BUTTON_NUM] = {2,3,4,5} ;
#endif