//
// Created by fbrier on 3/16/19.
//

#ifndef MOUSETRAPCAR_DRIVELEGS_H
#define MOUSETRAPCAR_DRIVELEGS_H


#include <USBAPI.h>

class DriveLegs
{
private:
// define the LED digit patterns, from 0 - 9
// 1 = LED on, 0 = LED off, in this order:
//                74HC595 pin     Q0,Q1,Q2,Q3,Q4,Q5,Q6,Q7
//                Mapping to      a,b,c,d,e,f,g of Seven-Segment LED
    const byte SEVEN_SEG_DIGITS[10] = { B11111100,  // = 0
                                  B01100000,  // = 1
                                  B11011010,  // = 2
                                  B11110010,  // = 3
                                  B01100110,  // = 4
                                  B10110110,  // = 5
                                  B10111110,  // = 6
                                  B11100000,  // = 7
                                  B11111110,  // = 8
                                  B11100110   // = 9
    };
    int _numberOfDriveLegs = 0;
    int _latchPin, _clockPin, _dataPin;
    void SevenSegWrite();

public:
    DriveLegs(int latchPin = 3, int clockPin = 4, int dataPin = 2);
    void SetDriveLegs(int numberOfDriveLegs);
    DriveLegs *operator++();
    DriveLegs *operator--();
    operator int () {return _numberOfDriveLegs;}
};


#endif //MOUSETRAPCAR_DRIVELEGS_H
