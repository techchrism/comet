//
// Created by Techdoodle on 1/19/2019.
//

#include <afxres.h>
#include "GuiVerticalMenu.h"

void GuiVerticalMenu::setup(string *header, int headerLength, string *options, int optionsLength)
{
    this->header = header;
    this->headerLength = headerLength;
    this->options = options;
    this->optionsLength = optionsLength;

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

    // For now we can ignore the header and bounding box and focus just on the menu
    short longestItemLength = 0;
    for(int i = 0; i < optionsLength; i++)
    {
        if(options[i].length() > longestItemLength)
        {
            longestItemLength = options[i].length();
        }
    }

    short arrowXOffset = 0;
    short rightArrowX = longestItemLength + 3;
    this->leftArrowTop = {arrowXOffset, 0};
    this->rightArrowTop = {rightArrowX, 0};
    this->yPos = 0;

    this->updateArrows();

    // Display the text
    this->writeOutput(this->leftArrowTop.X + 2, this->leftArrowTop.Y, this->centerText(options, optionsLength, longestItemLength), longestItemLength, optionsLength);
}

void GuiVerticalMenu::updateArrows()
{
    CHAR_INFO bufferLeft[this->optionsLength];
    CHAR_INFO bufferRight[this->optionsLength];

    COORD bufferSize = {1, static_cast<SHORT>(this->optionsLength)};
    short bottomY = this->leftArrowTop.Y + this->optionsLength - 1;
    SMALL_RECT writeAreaLeft = {this->leftArrowTop.X, this->leftArrowTop.Y, this->leftArrowTop.X, bottomY};
    SMALL_RECT writeAreaRight = {this->rightArrowTop.X, this->rightArrowTop.Y, this->rightArrowTop.X, bottomY};
    //SMALL_RECT writeAreaRight = {0, 0, 0, bottomY};

    for(int i = 0; i < this->optionsLength; i++)
    {
        if(i == this->yPos)
        {
            bufferLeft[i].Char.AsciiChar = '>';
            bufferLeft[i].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

            bufferRight[i].Char.AsciiChar = '<';
            bufferRight[i].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
        }
        else
        {
            bufferLeft[i].Char.AsciiChar = ' ';
            bufferLeft[i].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

            bufferRight[i].Char.AsciiChar = ' ';
            bufferRight[i].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
        }
    }

    WriteConsoleOutput(this->screenBuffer, bufferLeft, bufferSize, this->leftArrowTop, &writeAreaLeft);
    WriteConsoleOutput(this->screenBuffer, bufferRight, bufferSize, this->leftArrowTop, &writeAreaRight);
}

void GuiVerticalMenu::handleInput(int code)
{
}

void GuiVerticalMenu::handleArrow(int code)
{
    switch(code)
    {
        case KEY_UP:
        {
            if(yPos == 0)
            {
                yPos = optionsLength - 1;
            }
            else
            {
                yPos--;
            }
            updateArrows();
            break;
        }
        case KEY_DOWN:
        {
            if(yPos == optionsLength - 1)
            {
                yPos = 0;
            }
            else
            {
                yPos++;
            }
            updateArrows();
            break;
        }
        default:break;
    }
}