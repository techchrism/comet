//
// Created by Techdoodle on 1/18/2019.
//

#ifndef THEEDITOR_INPUTHANDLER_H
#define THEEDITOR_INPUTHANDLER_H


class InputHandler
{
public:
    virtual void handleInput(int code) {};
    virtual void handleArrow(int code) {};
};


#endif //THEEDITOR_INPUTHANDLER_H
