//
// Created by fbrier on 3/15/19.
//
#include <Arduino.h>
#include <HardwareSerial.h>
#include "CarControl.h"

CarControl control;

CarControl::CarControl() : _transmission(), _driveLegs(), _remoteControl()
{
}

CarControl::~CarControl()
{

}

void CarControl::Loop()
{
    _remoteControl.ProcessInput();
#ifdef TEST_STEPPER
    // step one revolution  in one direction:
  static int runNumber = 0;

  if (runNumber == 0)
  {
  Serial.println("\r\n\r\n\r\nclockwise");

   ChangeGear(FORWARD_GEAR);
   delay(1000);
   ChangeGear(NEUTRAL_F_GEAR);
   delay(1000);
   ChangeGear(FORWARD_GEAR);
   delay(1000);
   ChangeGear(BRAKE_GEAR);
   delay(1000);
   ChangeGear(NEUTRAL_F_GEAR);
   delay(1000);
   ChangeGear(REVERSE_GEAR);
   delay(1000);
   ChangeGear(NEUTRAL_R_GEAR);
   delay(1000);
   ChangeGear(FORWARD_GEAR);
   delay(1000);
  }
   delay(1000);
  runNumber++;
#endif

    // myStepper.step(stepsPerRevolution);
    // delay(250);

    // myStepper.step(0);
    // step one revolution in the other direction:
    // Serial.println("counterclockwise");
    // myStepper.step(-stepsPerRevolution);
    // delay(500);
/*
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
  */
    // wait for a second
}

void CarControl::Setup()
{
    attachInterrupt(0, DriveTickInterrupt, RISING);
    _remoteControl.RegisterHandler(BtnUpArrow, OnBtnUpArrow, this);
    _remoteControl.RegisterHandler(BtnDownArrow, OnBtnDownArrow, this);
    _remoteControl.RegisterHandler(BtnForward, OnBtnForward, this);
    _remoteControl.RegisterHandler(BtnReverse, OnBtnReverse, this);
    _remoteControl.RegisterHandler(BtnPlay_Pause, OnBtnPlay_Pause, this);
    _remoteControl.RegisterHandler(BtnPowerOn_Off, OnBtnPowerOn_Off, this);

    // initialize the serial port:
    Serial.begin(9600);

    pinMode(LED_BUILTIN, OUTPUT);
}

void CarControl::OnBtnUpArrow(void *obj)
{
    Serial.println("OnBtnUpArrow");
    ++((CarControl *)obj)->_driveLegs;
    ((CarControl *) obj)->CalcStopPoint();
}

void CarControl::OnBtnDownArrow(void *obj)
{
    CarControl * carControl = (CarControl *)obj;
    if (carControl->_driveLegs != 0)
    {
        --carControl->_driveLegs;
        carControl->CalcStopPoint();
    }
}

void CarControl::OnBtnForward(void *obj)
{
    CarControl * carControl = (CarControl *)obj;
    carControl->_curDriveLeg++;
    carControl->_numTicks = 0;
    carControl->_transmission.ChangeGear(FORWARD_GEAR);
}

void CarControl::OnBtnReverse(void *obj)
{
    CarControl * carControl = (CarControl *)obj;
    carControl->_curDriveLeg++;
    carControl->_numTicks = 0;
    carControl->_transmission.ChangeGear(REVERSE_GEAR);
}

void CarControl::OnBtnPlay_Pause(void *obj)
{
    CarControl * carControl = (CarControl *)obj;
    carControl->_transmission.ChangeGear(BRAKE_GEAR);
}

void CarControl::OnBtnPowerOn_Off(void *obj)
{
    CarControl * carControl = (CarControl *)obj;
    carControl->_transmission.ChangeGear(UNKNOWN_GEAR);
}

void CarControl::CalcStopPoint()
{
    _stopTicks = (K_MaxRotationInterruptCount / _driveLegs) - K_ReserveEnergy;
    Serial.print("Stop Ticks = ");
    Serial.println(_stopTicks);
    Serial.print("driveLegs = ");
    Serial.println((int)_driveLegs);
}

void CarControl::TickHandler()
{
    // If we are at the stop point
    if (_numTicks > _stopTicks)
    {
        // When going forward, move to the forward neutral position
        if (_curDriveLeg % 2)
            _transmission.ChangeGear(NEUTRAL_F_GEAR);
        else
            _transmission.ChangeGear(NEUTRAL_R_GEAR);
        // ToDo: Do we need to reset _numTicks to 0 for the new leg?
    }

    static bool ledState = false;
    if (ledState)
        digitalWrite(LED_BUILTIN, LOW);
    else
        digitalWrite(LED_BUILTIN, HIGH);

    ledState = !ledState;

}

/**
 * Use the single CarControl instance defined in the MouseCarTrap.ino file to call the non-static tick handler
 */
void CarControl::DriveTickInterrupt(void)
{
    control.TickHandler();
}
