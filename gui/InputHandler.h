//
// Created by Techdoodle on 1/18/2019.
//

#ifndef THEEDITOR_INPUTHANDLER_H
#define THEEDITOR_INPUTHANDLER_H


class InputHandler
{
public:
    virtual void handleInput(int code) = 0;
    virtual void handleArrow(int code) = 0;
    void onPush();
};


#endif //THEEDITOR_INPUTHANDLER_H
