//
// Created by Techdoodle on 2/27/2019.
//

#include <afxres.h>
#include "GuiTextBox.h"

GuiTextBox::GuiTextBox(string *data, int dataLength, WORD color)
{
    this->data = data;
    this->dataLength = dataLength;
    this->color = color;
    this->screenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
                                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                                   NULL,
                                                   CONSOLE_TEXTMODE_BUFFER,
                                                   NULL);
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = false;
    cursor.dwSize = 1;
    SetConsoleCursorInfo(this->screenBuffer, &cursor);

    render();
}

GuiTextBox::~GuiTextBox()
{
    delete data;
}

void GuiTextBox::render()
{
    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(screenBuffer, &buffInfo);

    // Find the longest string so the box can be properly sized
    int longestString = 0;
    for(int i = 0; i < dataLength; i++)
    {
        if(data[i].length() > longestString)
        {
            longestString = data[i].length();
        }
    }

    // Size the box
    short startX, startY, width, height;
    width = longestString + 6; // add 6 for borders)
    height = dataLength + 4; // Add 4 for borders
    startX = (buffInfo.dwSize.X / 2) - (width / 2);
    startY = (buffInfo.dwSize.Y / 2) - (height / 2);

    CHAR_INFO line[width];

    // Write the top and bottom borders
    line[0].Attributes = line[width - 1].Attributes = color;
    line[0].Char.AsciiChar = (unsigned char) 201;
    line[width - 1].Char.AsciiChar = (unsigned char) 187;
    for(int x = 1; x < width - 1; x++)
    {
        line[x].Attributes = color;
        line[x].Char.AsciiChar = (unsigned char) 205;
    }
    writeOutput(startX, startY, line, width, 1);

    line[0].Char.AsciiChar = (unsigned char) 200;
    line[width - 1].Char.AsciiChar = (unsigned char) 188;
    for(int x = 1; x < width - 1; x++)
    {
        line[x].Char.AsciiChar = (unsigned char) 205;
    }
    writeOutput(startX, startY + height - 1, line, width, 1);

    line[0].Char.AsciiChar = line[width - 1].Char.AsciiChar = (unsigned char) 186;
    for(int x = 1; x < width - 1; x++)
    {
        line[x].Attributes = WHITE_TEXT;
        line[x].Char.AsciiChar = ' ';
    }
    writeOutput(startX, startY + height - 2, line, width, 1);
    writeOutput(startX, startY + 1, line, width, 1);

    // Write the text data
    for(int y = 2; y < height - 2; y++)
    {
        int skipChars = (width - data[y - 2].length() - 6) / 2;
        for(int x = 3; x < width - 3; x++)
        {
            if(x - skipChars - 3 >= 0 && x - skipChars - 3 < data[y - 2].length())
            {
                line[x].Char.AsciiChar = data[y - 2][x - 3 - skipChars];
            }
            else
            {
                line[x].Char.AsciiChar = ' ';
            }
        }
        writeOutput(startX, startY + y, line, width, 1);
    }
}

void GuiTextBox::onResize()
{
    // Set the buffer size and clear it
    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(screenBuffer, &buffInfo);

    SetConsoleScreenBufferSize(screenBuffer, {static_cast<SHORT>(buffInfo.srWindow.Right + 1),
                                              static_cast<SHORT>(buffInfo.srWindow.Bottom + 1)});

    short xSize = buffInfo.srWindow.Right + 1;
    short ySize = buffInfo.srWindow.Bottom + 1;
    DWORD numChars;
    FillConsoleOutputCharacter(screenBuffer, ' ', xSize * ySize, {0, 0}, &numChars);
    FillConsoleOutputAttribute(screenBuffer, WHITE_TEXT, xSize * ySize, {0, 0}, &numChars);

    // Reset and re-render the data to the new buffer dimensions
    render();
}

void GuiTextBox::handleInput(int code)
{
    // Pop on any input
    manager->pop();
}