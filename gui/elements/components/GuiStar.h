//
// Created by Techdoodle on 2/9/2019.
//

#ifndef THEEDITOR_GUISTAR_H
#define THEEDITOR_GUISTAR_H

#include <Windows.h>

class GuiStar
{
private:
    bool shining = false;
    short x, y;
    HANDLE* buffer;
    short timeout = 0;

    void render();
public:
    GuiStar();
    void setup(short x, short y, HANDLE* buffer);
    void toggleChance();
};


#endif //THEEDITOR_GUISTAR_H
