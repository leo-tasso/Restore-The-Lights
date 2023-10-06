#define pot A0      //Pin of potentiometer
#define LS 13       //Pin of status LED, must be PWM pin
#define COLUMNS 4   //The number of pairs led-button

const unsigned short pinL[COLUMNS] = {6,7,8,9} ;
const unsigned short pinB[COLUMNS] = {2,3,4,5} ;

void waitStart();

void game();

void deepSleep();

void setup(){
    pinMode(pot,INPUT);
    pinMode(LS, OUTPUT);
    for(int i=0; i<COLUMNS; i++){
        pinMode(pinL[i],OUTPUT);
        pinMode(pinB[i],INPUT_PULLUP);
    }
    waitStart();
}

void loop() {
    deepSleep(); //In case Superloop is reached (it shouldn't) goes back to deepSleep state
}

void waitStart() {
    
}

 void game() {

 }

 void deepSleep() {
    
 }