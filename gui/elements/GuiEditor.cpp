//
// Created by Techdoodle on 1/21/2019.
//

#include <afxres.h>
#include "GuiEditor.h"

GuiEditor::GuiEditor()
{
    // Set up the buffer
    this->screenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
                                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                                   NULL,
                                                   CONSOLE_TEXTMODE_BUFFER,
                                                   NULL);
    SetConsoleMode(screenBuffer, ENABLE_WINDOW_INPUT | ENABLE_LINE_INPUT);
    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(screenBuffer, &buffInfo);
    this->borderXSize = buffInfo.dwSize.X;
    this->borderYSize = buffInfo.dwSize.Y;
    topMargin = 1;
    leftMargin = 2;
    lines.add(0, new LinkedList<char>);
    currentLine = lines.get(0);
    completeRender();
}

void GuiEditor::completeRender()
{
    // Write the borders

    // Clear the buffer
    DWORD numChars;
    FillConsoleOutputCharacter(screenBuffer, ' ', borderXSize * borderYSize, {0, 0}, &numChars);
    FillConsoleOutputAttribute(screenBuffer, WHITE_TEXT, borderXSize * borderYSize, {0, 0}, &numChars);

    // Draw the borders
    drawBorders(borderXSize, borderYSize);

    // Iterate through, drawing the lineas we go
    short lineLength = borderXSize - (leftMargin * 2);
    short currentLineNumber = 0;
    CHAR_INFO line[lineLength];
    LinkedListNode<LinkedList<char>*>* current = lines.getStart();
    while(current != nullptr)
    {
        // Iterate through the characters of the line
        LinkedListNode<char>* currentCh = current->getData()->getStart();
        for(int i = 0; i < lineLength; i++)
        {
            // If there is a character for this space, write it to the line, otherwise display a space
            if(currentCh != nullptr)
            {
                line[i].Char.AsciiChar = currentCh->getData();
                currentCh = currentCh->getNext();
            }
            else
            {
                line[i].Char.AsciiChar = ' ';
            }
            line[i].Attributes = WHITE_TEXT;
        }

        // Write the line
        writeOutput(leftMargin, topMargin + currentLineNumber, line, lineLength, 1);
        if(current->getNext() == nullptr)
        {
            // If this is the last line, set the cursor to the end
            cursorRelativeX = current->getData()->getLength();
            currentLine = current->getData();
        }
        current = current->getNext();
        currentLineNumber++;
    }

    // Set the cursor position to the end of the last line
    cursorRelativeY = lines.getLength() - 1;
    updateCursorPos();
}

void GuiEditor::drawBorders(short newX, short newY)
{
    // Top and bottom border
    CHAR_INFO horiz[newX];
    for(int i = 1; i < newX - 1; i++)
    {
        horiz[i].Attributes = WHITE_TEXT;
        horiz[i].Char.AsciiChar = (unsigned char) 205;
    }
    horiz[0].Attributes = horiz[newX - 1].Attributes = WHITE_TEXT;

    // Write with the top corners
    horiz[0].Char.AsciiChar = (unsigned char) 201;
    horiz[newX - 1].Char.AsciiChar = (unsigned char) 187;
    writeOutput(0, 0, horiz, newX, 1);

    // Write with the bottom corners
    horiz[0].Char.AsciiChar = (unsigned char) 200;
    horiz[newX - 1].Char.AsciiChar = (unsigned char) 188;
    writeOutput(0, newY - 1, horiz, newX, 1);

    // Left and right border
    CHAR_INFO vert[newY - 2];
    for(int i = 0; i < newY - 2; i++)
    {
        vert[i].Attributes = WHITE_TEXT;
        vert[i].Char.AsciiChar = (unsigned char) 186;
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
    drawBorders(newX + rightAdjust, newY + bottomAdjust);

    borderXSize = newX;
    borderYSize = newY;
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
        // Move everything else down a line
        if(cursorRelativeY + 1 < lines.getLength())
        {
            // If there's text below this, move it down
            move(leftMargin, topMargin + cursorRelativeY + 1, borderXSize - (leftMargin * 2), lines.getLength() - cursorRelativeY - 1, 0, 1, ' ');
        }

        // Move the text to a new line
        move(leftMargin + cursorRelativeX, topMargin + cursorRelativeY, currentLine->getLength(), 1, -1 * cursorRelativeX, 1, ' ');

        // If there's text on the current line, split it
        // Otherwise, make the new line empty
        LinkedList<char>* insertedLine = new LinkedList<char>;
        if(cursorRelativeX != currentLine->getLength())
        {
            insertedLine->add(0, currentLine->split(cursorRelativeX));
        }
        lines.add(cursorRelativeY + 1, insertedLine);
        currentLine = insertedLine;

        cursorRelativeY++;
        cursorRelativeX = 0;
        updateCursorPos();
    }
    else if(code == KEY_BACKSPACE)
    {
        // Backspace a character
        if(cursorRelativeX == 0)
        {
            // Remove the line (if not at the top row)
            if(cursorRelativeY != 0)
            {
                LinkedList<char>* prev = lines.get(cursorRelativeY - 1);

                // Move the line up to the end of the one above
                move(leftMargin, topMargin + cursorRelativeY, currentLine->getLength(), 1, prev->getLength(), -1, ' ');

                // Move everything else up
                move(leftMargin, topMargin + cursorRelativeY + 1, borderXSize - (leftMargin * 2), lines.getLength() - cursorRelativeY - 1, 0, -1, ' ');

                // Update cursor position to the merge point
                cursorRelativeY--;
                cursorRelativeX = prev->getLength();
                updateCursorPos();

                // Update the linked list
                prev->add(prev->getLength(), currentLine->getStart());
                lines.remove(cursorRelativeY + 1, false, false);
                currentLine = lines.get(cursorRelativeY);
            }
        }
        else
        {
            // Remove just the character
            move(leftMargin + cursorRelativeX, topMargin + cursorRelativeY, currentLine->getLength(), 1, -1, 0, ' ');
            cursorRelativeX--;
            currentLine->remove(cursorRelativeX);
            updateCursorPos();
        }
    }
    else
    {
        // If it's any character without a special case
        if(cursorRelativeX < currentLine->getLength())
        {
            // If we're in a line, move all the other characters back
            // Because it's just being moved back one space, we can make the fill character the entered one
            move(leftMargin + cursorRelativeX, topMargin + cursorRelativeY, currentLine->getLength(), 1, 1, 0, code);
        }
        else
        {
            // If it's at the end of the line, add it
            CHAR_INFO ch[1];
            ch[0].Char.AsciiChar = code;
            ch[0].Attributes = WHITE_TEXT;
            writeOutput(leftMargin + cursorRelativeX, topMargin + cursorRelativeY, ch, 1, 1);
        }
        currentLine->add(cursorRelativeX, code);
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
            if(cursorRelativeY != 0)
            {
                cursorRelativeY--;
                currentLine = lines.get(cursorRelativeY);

                if(currentLine->getLength() < cursorRelativeX)
                {
                    cursorRelativeX = currentLine->getLength();
                }
                updateCursorPos();
            }
            break;
        }
        case KEY_DOWN:
        {
            if(cursorRelativeY != lines.getLength() - 1)
            {
                cursorRelativeY++;
                currentLine = lines.get(cursorRelativeY);

                if(currentLine->getLength() < cursorRelativeX)
                {
                    cursorRelativeX = currentLine->getLength();
                }
                updateCursorPos();
            }
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