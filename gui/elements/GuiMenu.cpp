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
    COORD bufferCoord = {0, 0};
    SMALL_RECT writeArea = {1, 1, 6, 6};
    CHAR_INFO buffer[5 * 5];

    for(int i = 0; i < 5 * 5; i++)
    {
        buffer[i].Char.AsciiChar = '=';
        buffer[i].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    }

    WriteConsoleOutput(this->screenBuffer, buffer, bufferSize, bufferCoord, &writeArea);
}

void GuiMenu::handleArrow(int code)
{

}

void GuiMenu::handleInput(int code)
{

}