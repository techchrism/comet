//
// Created by Techdoodle on 2/9/2019.
//

#include <afxres.h>
#include "GuiAnimationTest.h"

GuiAnimationTest::GuiAnimationTest()
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
    star.setup(3, 3, &screenBuffer);
}

void GuiAnimationTest::handleAnimationFrame(unsigned long count)
{
    string countStr = to_string(count);
    CHAR_INFO chars[countStr.length()];
    for(int i = 0; i < countStr.length(); i++)
    {
        chars[i].Attributes = WHITE_TEXT;
        chars[i].Char.AsciiChar = countStr[i];
    }
    writeOutput(0, 0, chars, countStr.length(), 1);
    star.toggleChance();
}