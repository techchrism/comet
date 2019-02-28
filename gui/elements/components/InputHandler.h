//
// Created by Techdoodle on 1/18/2019.
//

#ifndef THEEDITOR_INPUTHANDLER_H
#define THEEDITOR_INPUTHANDLER_H

#define KEY_UP 0x26
#define KEY_DOWN 0x28
#define KEY_LEFT 0x25
#define KEY_RIGHT 0x27

#define KEY_BACKSPACE 8
#define KEY_DELETE 127
#define KEY_ENTER 13
#define KEY_ESC 27

class InputHandler
{
public:
    virtual void handleInput(int code) {};
    virtual void handleArrow(int code) {};
    virtual void handleCtrl(int code) {};
    virtual void handleMouse(MOUSE_EVENT_RECORD m) {};
    virtual void handleAnimationFrame(unsigned long frame) {};
};


#endif //THEEDITOR_INPUTHANDLER_H
