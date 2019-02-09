//
// Created by Techdoodle on 1/18/2019.
//

#include <afxres.h>
#include "GuiMenu.h"

GuiMenu::GuiMenu()
{
    // Create the console buffer
    this->screenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
                                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                                   NULL,
                                                   CONSOLE_TEXTMODE_BUFFER,
                                                   NULL);

    // Hide cursor for menus
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = false;
    cursor.dwSize = 1;
    SetConsoleCursorInfo(this->screenBuffer, &cursor);

    // Display a 5x5 square of squares
    COORD bufferSize = {5, 5};
    CHAR_INFO buffer[1 * 10];

    for(int i = 0; i < 1 * 10; i++)
    {
        if(i % 2 == 0)
        {
        }
        else
        {
            buffer[i].Attributes = WHITE_TEXT;
            buffer[i].Char.AsciiChar = '=';
        }
    }

    writeOutput(0, 0, buffer, 10, 2);
    //WriteConsoleOutput(this->screenBuffer, buffer, bufferSize, bufferCoord, &writeArea);
}

void GuiMenu::handleArrow(int code)
{

}

void GuiMenu::handleInput(int code)
{

}