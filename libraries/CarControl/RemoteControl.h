//
// Created by fbrier on 3/16/19.
//

#ifndef MOUSETRAPCAR_REMOTECONTROL_H
#define MOUSETRAPCAR_REMOTECONTROL_H

#include "IRremote/IRremote.h"
#define IR_IN_PIN 13

typedef void (*HandlerFunction)(void *);
#define MAX_HANDLERS 6

class EventHandler
{
    HandlerFunction _func;
    void *_obj;
public:
    EventHandler(HandlerFunction _func, void *_obj) : _func(_func), _obj(_obj) {}
    void Execute() {(*_func)(_obj);}
};

typedef enum
{
    BtnUpArrow = 0,
    BtnDownArrow = 1,
    BtnForward = 2,
    BtnReverse = 3,
    BtnPlay_Pause = 4,
    BtnPowerOn_Off = 5

} RemoteEventType;

class RemoteControl
{
private:
    IRrecv irReceiver;
    decode_results _results;
    EventHandler *_handlers[MAX_HANDLERS];

    void ExecuteHandler(RemoteEventType event);
    void TranslateIR(decode_results *results);

public:
    RemoteControl();
    void ProcessInput();
    void RegisterHandler(RemoteEventType event, HandlerFunction handler, void *userData);
    virtual ~RemoteControl();
};


#endif //MOUSETRAPCAR_REMOTECONTROL_H
