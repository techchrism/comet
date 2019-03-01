//
// Created by Techdoodle on 1/18/2019.
//

#ifndef THEEDITOR_GUIFRAME_H
#define THEEDITOR_GUIFRAME_H

#include <windows.h>
#include "InputHandler.h"
#include "../../GuiManager.h"
#include <iostream>
#include <fcntl.h>

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
    void writeAttribute(short x, short y, WORD attribute, short length);
    void writeString(short x, short y, string data);
    void writeString(short x, short y, string data, WORD attribute);

    void move(short x, short y, short length, short height, short distanceX, short distanceY, char fillch);
public:
    // Designed to be optionally overridden
    virtual void onActivate()
    {
        SetConsoleActiveScreenBuffer(this->screenBuffer);
    };
    virtual void onResize() {};

    // Designed for the editor to override
    virtual void saveState(){};

    void setManager(GuiManager* manager);
    HANDLE getBuffer();
};

#endif //THEEDITOR_GUIFRAME_H
