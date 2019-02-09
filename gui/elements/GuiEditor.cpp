//
// Created by Techdoodle on 1/21/2019.
//

#include <afxres.h>
#include "GuiEditor.h"

GuiEditor::GuiEditor()
{
    this->screenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
                                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                                   NULL,
                                                   CONSOLE_TEXTMODE_BUFFER,
                                                   NULL);
    SetConsoleMode(screenBuffer, ENABLE_WINDOW_INPUT | ENABLE_LINE_INPUT);
    topMargin = 1;
    leftMargin = 1;
    SetConsoleCursorPosition(screenBuffer, {leftMargin, topMargin});
    lines.add(0, new LinkedList<char>);
    currentLine = lines.get(0);

    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(screenBuffer, &buffInfo);
    this->borderXSize = buffInfo.dwSize.X;
    this->borderYSize = buffInfo.dwSize.Y;

    completeReRender();
}

void GuiEditor::completeReRender()
{
    // Write the borders
    // Bottom/right borders
    this->resizeBorders(0, 0, borderXSize, borderYSize);
}

void GuiEditor::resizeBorders(short oldX, short oldY, short newX, short newY)
{
    // Top and bottom border
    CHAR_INFO horiz[newX];
    for(int i = 1; i < newX - 1; i++)
    {
        horiz[i].Attributes = WHITE_TEXT;
        horiz[i].Char.AsciiChar = '#';
    }
    horiz[0].Attributes = horiz[newX - 1].Attributes = WHITE_TEXT;
    horiz[0].Char.AsciiChar = horiz[newX - 1].Char.AsciiChar = '+';
    writeOutput(0, 0, horiz, newX, 1);
    writeOutput(0, newY - 1, horiz, newX, 1);

    // Left and right border
    CHAR_INFO vert[newY - 2];
    for(int i = 0; i < newY - 2; i++)
    {
        vert[i].Attributes = WHITE_TEXT;
        vert[i].Char.AsciiChar = '#';
    }
    writeOutput(0, 1, vert, 1, newY - 2);
    writeOutput(newX - 1, 1, vert, 1, newY - 2);
}

void GuiEditor::resizeBuffer(short newX, short newY)
{
    // Get the old buffer size
    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(screenBuffer, &buffInfo);
    short oldX = buffInfo.dwSize.X;
    short oldY = buffInfo.dwSize.Y;

    // Remove the complete right side and bottom side
    CHAR_INFO rightWipe[borderYSize];
    for(int i = 0; i < borderYSize; i++)
    {
        rightWipe[i].Char.AsciiChar = ' ';
        rightWipe[i].Attributes = WHITE_TEXT;
    }
    writeOutput(borderXSize - 1, 0, rightWipe, 1, borderYSize);

    CHAR_INFO bottomWipe[borderXSize];
    for(int i = 0; i < borderXSize; i++)
    {
        bottomWipe[i].Char.AsciiChar = ' ';
        bottomWipe[i].Attributes = WHITE_TEXT;
    }
    writeOutput(0, borderYSize - 1, bottomWipe, borderXSize, 1);

    // Resize the buffer
    SetConsoleScreenBufferSize(screenBuffer, {newX, newY});

    // Get the new buffer size (changes because of scroll bars)
    GetConsoleScreenBufferInfo(screenBuffer, &buffInfo);

    short bottomAdjust = 0;
    short rightAdjust = 0;

    // Test if there's a right scroll bar blocking stuff
    if(buffInfo.srWindow.Bottom - buffInfo.srWindow.Top < newY)
    {
        rightAdjust = -2;
    }

    // Test if there's a bottom scroll bar blocking stuff
    if(buffInfo.srWindow.Right - buffInfo.srWindow.Left < newX)
    {
        bottomAdjust = -1;
    }

    // Rewrite the border
    resizeBorders(oldX, oldY, newX + rightAdjust, newY + bottomAdjust);

    borderXSize = newX;
    borderYSize = newY;
}

void GuiEditor::printLinkedList(short x, short y, LinkedList<char> data)
{
    CHAR_INFO chars[data.getLength()];
    LinkedListNode<char>* current = data.getStart();
    for(int i = 0; i < data.getLength(); i++)
    {
        chars[i].Char.AsciiChar = current->getData();
        current = current->getNext();
    }
    writeOutput(x, y, chars, data.getLength(), 1);
}

void GuiEditor::updateCursorPos()
{
    SetConsoleCursorPosition(screenBuffer, {static_cast<SHORT>(leftMargin + cursorRelativeX),
                                            static_cast<SHORT>(topMargin + cursorRelativeY)});
}

void GuiEditor::handleInput(int code)
{
    if(code == KEY_ENTER)
    {
        // Move the text to a new line
        SMALL_RECT from;
        from.Top = topMargin + cursorRelativeY;
        from.Left = leftMargin + cursorRelativeX;
        from.Bottom = topMargin + cursorRelativeY;
        from.Right = leftMargin + currentLine->getLength();

        COORD to;
        to.X = leftMargin;
        to.Y = topMargin + cursorRelativeY + 1;

        CHAR_INFO fill;
        fill.Attributes = WHITE_TEXT;
        fill.Char.AsciiChar = ' ';

        //ScrollConsoleScreenBuffer(screenBuffer, &from, nullptr, to, fill);
        ScrollConsoleScreenBuffer(screenBuffer, &from, nullptr, to, &fill);

        // If there's text on the current line, split it
        // Otherwise, make the new line empty
        LinkedList<char>* insertedLine = new LinkedList<char>;
        if(cursorRelativeX != currentLine->getLength())
        {
            insertedLine->add(0, currentLine->split(cursorRelativeX));
        }
        lines.add(cursorRelativeY + 1, insertedLine);
        //printLinkedList(leftMargin, topMargin + cursorRelativeY + 1, *insertedLine);

        // Move everything else down a line



        cursorRelativeY++;
        cursorRelativeX = 0;
        updateCursorPos();

        /*CHAR_INFO testSquare[5 * 5];
        for(int i = 0; i < 5 * 5; i++)
        {
            testSquare[i].Char.AsciiChar = '*';
            testSquare[i].Attributes = WHITE_TEXT;
        }
        writeOutput(2, 2, testSquare, 5, 5);*/
    }
    else
    {
        currentLine->add(cursorRelativeX, code);
        CHAR_INFO ch[1];
        ch[0].Char.AsciiChar = code;
        ch[0].Attributes = WHITE_TEXT;
        writeOutput(leftMargin + cursorRelativeX, topMargin + cursorRelativeY, ch, 1, 1);
        cursorRelativeX++;
        updateCursorPos();
    }
}

void GuiEditor::handleArrow(int code)
{
    switch(code)
    {
        case KEY_UP:
        {
            //resizeBuffer(borderXSize, borderYSize + 1);
            break;
        }
        case KEY_DOWN:
        {
            //resizeBuffer(borderXSize, borderYSize - 1);
            break;
        }
        case KEY_LEFT:
        {
            // If we have to move it up a line
            if(cursorRelativeX == 0)
            {
                // If we're already on the first line, we can't really do anything
                if(cursorRelativeY == 0)
                {

                }
                else
                {
                    // Otherwise, move it to the end of the next line
                    cursorRelativeY--;
                    currentLine = lines.get(cursorRelativeY);
                    cursorRelativeX = currentLine->getLength();
                }
            }
            else
            {
                cursorRelativeX--;
            }

            updateCursorPos();
            break;
        }
        case KEY_RIGHT:
        {
            // If we have to move it down a line
            if(cursorRelativeX == currentLine->getLength())
            {
                // If we're already on the last line, we can't really do anything
                if(lines.getLength() == cursorRelativeY + 1)
                {

                }
                else
                {
                    // Otherwise, move it to the start of the next line
                    cursorRelativeX = 0;
                    cursorRelativeY++;
                    currentLine = lines.get(cursorRelativeY);
                }
            }
            else
            {
                cursorRelativeX++;
            }

            updateCursorPos();
            break;
        }
    }
}