//
// Created by Techdoodle on 1/18/2019.
//

#include <afxres.h>
#include "GuiFrame.h"

void GuiFrame::setCursorPos(short x, short y)
{
    SetConsoleCursorPosition(this->screenBuffer, {x, y});
}

void GuiFrame::setManager(GuiManager *manager)
{
    this->manager = manager;
}

void GuiFrame::move(short x, short y, short length, short height, short distanceX, short distanceY, char fillch)
{
    SMALL_RECT from;
    from.Top = y;
    from.Bottom = y + height - 1;
    from.Left = x;
    from.Right = x + length - 1;

    COORD to;
    to.X = x + distanceX;
    to.Y = y + distanceY;

    CHAR_INFO fill;
    fill.Attributes = WHITE_TEXT;
    fill.Char.AsciiChar = fillch;
    ScrollConsoleScreenBuffer(screenBuffer, &from, nullptr, to, &fill);
}

CHAR_INFO* GuiFrame::centerText(string *text, int textLength, int horizontalSize)
{
    // Centers text line-by-line
    CHAR_INFO* textBuffer = new CHAR_INFO[horizontalSize * textLength];
    for(int y = 0; y < textLength; y++)
    {
        for(int x = 0; x < horizontalSize; x++)
        {
            CHAR_INFO c;
            c.Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

            int difference = horizontalSize - text[y].length();
            int leftGap = (difference / 2);

            // If it's in range to start printing text
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

CHAR_INFO* GuiFrame::centerText(string text, int horizontalSize)
{
    string arr[1];
    arr[0] = text;
    return centerText(arr, 1, horizontalSize);
}

void GuiFrame::writeOutput(short x, short y, CHAR_INFO *text, short columns, short rows)
{
    short finishX = x + columns;
    short finishY = y + rows;
    SMALL_RECT box = {x, y, finishX, finishY};

    WriteConsoleOutput(this->screenBuffer, text, {columns, rows}, {0, 0}, &box);
}

void GuiFrame::writeAttribute(short x, short y, WORD attribute, short length)
{
    DWORD written;
    WORD data[length];
    for(int i = 0; i < length; i++)
    {
        data[i] = attribute;
    }
    WriteConsoleOutputAttribute(this->screenBuffer, data, length, {x, y}, &written);
}

void GuiFrame::writeString(short x, short y, string data)
{
    writeString(x, y, data, WHITE_TEXT);
}

CHAR_INFO* GuiFrame::setColor(CHAR_INFO* data, int length, WORD color)
{
    for(int i = 0; i < length; i++)
    {
        data[i].Attributes = color;
    }
    return data;
}

void GuiFrame::writeString(short x, short y, string data, WORD attribute)
{
    // Creates a CHAR_INFO array of the right size and fills it with the string data
    CHAR_INFO chars[data.length()];
    for(int i = 0; i < data.length(); i++)
    {
        chars[i].Attributes = attribute;
        chars[i].Char.AsciiChar = data[i];
    }
    writeOutput(x, y, chars, data.length(), 1);
}

HANDLE GuiFrame::getBuffer()
{
    return screenBuffer;
}