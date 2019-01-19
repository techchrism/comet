//
// Created by Techdoodle on 1/18/2019.
//

#ifndef THEEDITOR_GUIFRAME_H
#define THEEDITOR_GUIFRAME_H

#include <windows.h>
#include "InputHandler.h"

class GuiFrame : public InputHandler
{
protected:
    HANDLE screenBuffer;
    void setCursorPos(short x, short y);
public:
    // Designed to be optionally overridden
    virtual void onActivate()
    {
        SetConsoleActiveScreenBuffer(this->screenBuffer);
    };

    void onResize() {};

    //virtual void setup() = 0;
};

#endif //THEEDITOR_GUIFRAME_H
