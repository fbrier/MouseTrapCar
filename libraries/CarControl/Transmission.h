//
// Created by fbrier on 3/15/19.
//

#ifndef MOUSETRAPCAR_TRANSMISSION_H
#define MOUSETRAPCAR_TRANSMISSION_H

// NF - Neutral
// F - Forward
// R - Reverse
// B - Break
// FROM_TO

#include <Arduino.h>
#include "Stepper/src/Stepper.h"

#define NF_F -1000
#define F_B -150
#define B_R -250
#define R_NR -1000
#define NR_R +1000
#define R_B +150
#define B_F +250
#define F_NF +1000

#define DRIVE_ROT_INPUT_PIN 2

enum GearPositions
{
    UNKNOWN_GEAR,
    FORWARD_GEAR,
    REVERSE_GEAR,
    NEUTRAL_F_GEAR,
    NEUTRAL_R_GEAR,
    BRAKE_GEAR
};

/**
  Stepper Motor Control - one revolution

  This program drives a unipolar or bipolar stepper motor.
  The motor is attached to digital pins 8 - 11 of the Arduino.
*/
class Transmission
{
private:
    const String GEAR_NAMES[6] = { "UnK-Gear", "F-Gear", "R-Gear", "NF_Gear", "NR_Gear", "Brake" };

    const int K_StepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
    const int K_RolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
    int _currentGear;
    int _numSteps;
    Stepper _stepper;
public:
    Transmission();

    void Init();
    int GoForward();
    int GoReverse();
    int GoNeutral();
    int GoBrake();
    void ChangeGear(int requestedGear);
};
#endif //MOUSETRAPCAR_TRANSMISSION_H
