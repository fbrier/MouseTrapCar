//
// Created by fbrier on 3/16/19.
//

#include "DriveLegs.h"
//www.elegoo.com
//2016.12.12



// connect to the ST_CP of 74HC595 (pin 3,latch pin)
// connect to the SH_CP of 74HC595 (pin 4, clock pin)
// connect to the DS of 74HC595 (pin 2)
DriveLegs::DriveLegs(int latchPin, int clockPin, int dataPin) : _latchPin(latchPin), _clockPin(clockPin), _dataPin(dataPin)
{
    // Set latchPin, clockPin, dataPin as output
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    SetDriveLegs(1);
}

// display a number on the digital segment display
void DriveLegs::SevenSegWrite()
{
    // set the latchPin to low potential, before sending data
    digitalWrite(_latchPin, LOW);

    // the original data (bit pattern)
    shiftOut(_dataPin, _clockPin, LSBFIRST, SEVEN_SEG_DIGITS[_numberOfDriveLegs]);

    // set the latchPin to high potential, after sending data
    digitalWrite(_latchPin, HIGH);
}

void DriveLegs::SetDriveLegs(int numberOfDriveLegs)
{
    _numberOfDriveLegs = numberOfDriveLegs;
    SevenSegWrite();
}

DriveLegs *DriveLegs::operator++()
{
    SetDriveLegs(++_numberOfDriveLegs);
    return this;
}

DriveLegs *DriveLegs::operator--()
{
    SetDriveLegs(--_numberOfDriveLegs);
    return this;
}

/*
void loop() {
    // count from 9 to 0
    for (byte digit = 10; digit > 0; --digit) {
        delay(1000);
        sevenSegWrite(digit - 1);
    }

    // suspend 4 seconds
    delay(3000);
}
*/

