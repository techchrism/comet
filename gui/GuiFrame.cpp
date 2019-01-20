//
// Created by Techdoodle on 1/18/2019.
//

#include "GuiFrame.h"

void GuiFrame::setCursorPos(short x, short y)
{
    SetConsoleCursorPosition(this->screenBuffer, {x, y});
}

void GuiFrame::setManager(GuiManager *manager)
{
    this->manager = manager;
}

CHAR_INFO* GuiFrame::centerText(string *text, int textLength, int horizontalSize)
{
    CHAR_INFO* textBuffer = new CHAR_INFO[horizontalSize * textLength];
    for(int y = 0; y < textLength; y++)
    {
        for(int x = 0; x < horizontalSize; x++)
        {
            CHAR_INFO c;
            c.Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

            int difference = horizontalSize - text[y].length();
            int leftGap = (difference / 2);

            if(x < leftGap || x >= (leftGap + text[y].length()))
            {
                c.Char.AsciiChar = ' ';
            }
            else
            {
                c.Char.AsciiChar = text[y][x - leftGap];
            }

            textBuffer[x + (horizontalSize * y)] = c;
        }
    }

    return textBuffer;
}

void GuiFrame::writeOutput(short x, short y, CHAR_INFO *text, short columns, short rows)
{
    short finishX = x + columns;
    short finishY = y + rows;
    SMALL_RECT box = {x, y, finishX, finishY};

    WriteConsoleOutput(this->screenBuffer, text, {columns, rows}, {0, 0}, &box);
}