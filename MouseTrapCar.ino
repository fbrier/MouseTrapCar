#include "CarControl/CarControl.h"


// initialize the stepper library on pins 8 through 11:

extern CarControl control;


//===================================================
//===================================================
void setup()
{
    control.Setup();
}

//===================================================
//===================================================
void loop() 
{
    control.Loop();
}

