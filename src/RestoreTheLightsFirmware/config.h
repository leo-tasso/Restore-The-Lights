#ifndef CONFIG
#define CONFIG

#define DEBUG

#define pot A0                  //Pin of potentiometer
#define LS 11                   //Pin of status LED, must be PWM pin
#define BUTTON_NUM 4            //The number of pairs led-button (MAX 8)
#define MAX_WAIT_TIME 1000
#define MIN_WAIT_TIME 1
#define T2_TIME_DEFAULT 1500
#define T3_TIME_DEFAULT 5000
#define BOUNCING_TIME 30 //ms
#define INVERTED 1
enum game_state { START_READY,
                  WAIT_START_TIME,
                  DISPLAY_SEQUENCE,
                  USER_GAMEPLAY,
                  SLEEP };
const unsigned short pinL[BUTTON_NUM] = { 9,8,7,6 };
const unsigned short pinB[BUTTON_NUM] = { 2, 3, 4, 5 };
#endif