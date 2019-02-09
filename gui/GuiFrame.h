//
// Created by Techdoodle on 1/18/2019.
//

#ifndef THEEDITOR_GUIFRAME_H
#define THEEDITOR_GUIFRAME_H

#include <windows.h>
#include "InputHandler.h"
#include "GuiManager.h"
#include <iostream>

using namespace std;

#define WHITE_TEXT FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED

// Forward definition is needed to resolve mutual dependencies
class GuiManager;

class GuiFrame : public InputHandler
{
protected:
    GuiManager* manager;
    HANDLE screenBuffer;

    // Convenience functions
    void setCursorPos(short x, short y);
    CHAR_INFO* centerText(string* text, int textLength, int horizontalSize);
    void writeOutput(short x, short y, CHAR_INFO* text, short columns, short rows);
public:
    // Designed to be optionally overridden
    virtual void onActivate()
    {
        SetConsoleActiveScreenBuffer(this->screenBuffer);
    };
    virtual void onResize() {};

    void setManager(GuiManager* manager);
};

#endif //THEEDITOR_GUIFRAME_H
