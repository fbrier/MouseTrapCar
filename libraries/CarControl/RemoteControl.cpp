//
// Created by fbrier on 3/16/19.
//

#include "RemoteControl.h"

RemoteControl::RemoteControl() : irReceiver(IR_IN_PIN)
{
    for(int i = 0; i < MAX_HANDLERS; i++)
    {
        _handlers[i] = NULL;
    }
    irReceiver.enableIRIn();
}

RemoteControl::~RemoteControl()
{
    for(int i = 0; i < MAX_HANDLERS; i++)
    {
        if (NULL != _handlers[i])
        {
            delete _handlers[i];
            _handlers[i] = NULL;
        }
    }
}

/**
 * This is called in the main Loop() method.
 */
void RemoteControl::ProcessInput()
{
    decode_results results;
    if (irReceiver.decode(&results))
    {
        TranslateIR(&results);
        irReceiver.resume();
        Serial.print(".");
    }
}

void RemoteControl::RegisterHandler(RemoteEventType event, HandlerFunction handler, void *userData)
{
    if (NULL != _handlers[event])
    {
        delete _handlers[event];
    }
    _handlers[event] = new EventHandler(handler, userData);
}

void RemoteControl::ExecuteHandler(RemoteEventType event)
{
    // ToDo: Check for null handler, or just let it die?
    _handlers[event]->Execute();
}

void RemoteControl::TranslateIR(decode_results *results)
{
    switch (results->value)
    {

        case 0xff22dd:  Serial.println("Back"); break;
        case 0xffc23d:  Serial.println("Forward"); break;

        case 0xff6897:  Serial.println("0"); break;
        case 0xff9867:  Serial.println("eq"); break;
        case 0xffb04f:  Serial.println("step"); break;
        case 0xff30cf:  Serial.println("1"); break;
        case 0xff18e7:  Serial.println("2"); break;
        case 0xff7a85:  Serial.println("3"); break;
        case 0xff10ef:  Serial.println("4"); break;
        case 0xff38c7:  Serial.println("5"); break;
        case 0xff5aa5:  Serial.println("6"); break;
        case 0xff42bd:  Serial.println("7"); break;
        case 0xff4ab5:  Serial.println("8"); break;
        case 0xff52ad:  Serial.println("9"); break;
        case 0xffffffff:  Serial.println("Repeat"); break;
        case 0xFFE21D: Serial.println("Function"); break;

        case 0xFFA25D:
            Serial.println("PowerOn/Off");
            ExecuteHandler(BtnPowerOn_Off);
            break;
        case 0xff629d:
            Serial.println("Vol+");
            ExecuteHandler(BtnForward);
            break;
        case 0xffa857:
            Serial.println("Vol-");
            ExecuteHandler(BtnReverse);
            break;
        case 0xFF02FD:
            Serial.println("Play\\Pause");
            ExecuteHandler(BtnPlay_Pause);
            break;
        case 0xFFE01F:
            Serial.println("Down");
            ExecuteHandler(BtnDownArrow);
            break;
        case 0xFF906F:
            Serial.println("Up");
            ExecuteHandler(BtnUpArrow);
            break;

        default:
            Serial.print("Value not listed : 0x");
            Serial.println(_results.value, HEX);

    }
    // ToDo: Wish we could get rid of this and use interrupts
    delay(500); // Stop from getting an immediate repeat
}
