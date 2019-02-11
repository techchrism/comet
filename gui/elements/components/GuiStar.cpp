//
// Created by Techdoodle on 2/9/2019.
//

#include <afxres.h>
#include "GuiStar.h"

GuiStar::GuiStar()
{

}

void GuiStar::setup(short x, short y, HANDLE *buffer)
{
    this->x = x;
    this->y = y;
    this->buffer = buffer;
    render();
}

void GuiStar::render()
{
    CHAR_INFO text[1];
    text[0].Char.AsciiChar = '*';
    if(shining)
    {
        // 14 - yellow
        text[0].Attributes = 14;
    }
    else
    {
        text[0].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    }
    SMALL_RECT box = {x, y, static_cast<SHORT>(x + 1), static_cast<SHORT>(y + 1)};
    WriteConsoleOutput(*buffer, text, {1, 1}, {0, 0}, &box);
}

void GuiStar::toggleChance()
{
    if(shining)
    {
        // If it's shining, delay some so it doesn't immediately flicker
        timeout--;
        if(timeout <= 0)
        {
            shining = false;
            render();
        }
    }
    else
    {
        // Make it a 1 in 200 chance to toggle
        if((rand() % 1000) < 5)
        {
            shining = true;
            timeout = 30;
            render();
        }
    }
}