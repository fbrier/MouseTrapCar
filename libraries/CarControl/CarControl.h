//
// Created by fbrier on 3/15/19.
//

#ifndef MOUSETRAPCAR_CARCONTROL_H
#define MOUSETRAPCAR_CARCONTROL_H

#include "Transmission.h"
#include "DriveLegs.h"
#include "RemoteControl.h"

// Number of interrupts where all energy is used from the trap
#define K_MaxRotationInterruptCount 400

// The amount of energy to save for each turn around leg
#define K_ReserveEnergy 10

class  CarControl
{
private:
    Transmission _transmission;
    DriveLegs _driveLegs;
    RemoteControl _remoteControl;
    unsigned int _stopTicks = 0;
    unsigned int _curDriveLeg = 0;
    unsigned int _numTicks = 0;
    void TickHandler();

    // Infrared remote event handlers
    static void OnBtnUpArrow(void *obj);
    static void OnBtnDownArrow(void *obj);
    static void OnBtnForward(void *obj);
    static void OnBtnReverse(void *obj);
    static void OnBtnPlay_Pause(void *obj);
    static void OnBtnPowerOn_Off(void *obj);

public:
    CarControl();

    virtual ~CarControl();

    void Setup();
    void Loop();
    void CalcStopPoint();
    static void DriveTickInterrupt(void);
};

#endif //MOUSETRAPCAR_CARCONTROL_H
