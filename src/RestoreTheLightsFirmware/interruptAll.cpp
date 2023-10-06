#include "interruptAll.h"
#include "config.h"
#include <EnableInterrupt.h>

void allButtonsAttachIntterrupt(void (*attachedFunction)()){
    for (int i = 0; i < COLUMNS; i++)    {
        enableInterrupt(pinB[i], attachedFunction, CHANGE);
    }
}
void allButtonsDetatchIntterrupt(){
    for (int i = 0; i < COLUMNS; i++)    {
        disableInterrupt(pinB[i]);
    }
}