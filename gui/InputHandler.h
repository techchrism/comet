//
// Created by Techdoodle on 1/18/2019.
//

#ifndef THEEDITOR_INPUTHANDLER_H
#define THEEDITOR_INPUTHANDLER_H

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define KEY_BACKSPACE 8
#define KEY_DELETE 127

class InputHandler
{
public:
    virtual void handleInput(int code) {};
    virtual void handleArrow(int code) {};
};


#endif //THEEDITOR_INPUTHANDLER_H
