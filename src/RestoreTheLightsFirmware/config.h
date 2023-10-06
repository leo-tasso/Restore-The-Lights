#ifndef CONFIG
#define CONFIG

#define pot A0      //Pin of potentiometer
#define LS 13       //Pin of status LED, must be PWM pin
#define COLUMNS 4   //The number of pairs led-button

const unsigned short pinL[COLUMNS] = {6,7,8,9} ;
const unsigned short pinB[COLUMNS] = {2,3,4,5} ;
#endif