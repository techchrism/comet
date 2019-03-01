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
    SetConsoleMode(screenBuffer, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT & ~ENABLE_QUICK_EDIT_MODE);

    lines.add(0, new LinkedList<char>);
    currentLine = lines.get(0);

    header = "[Comet Editor]";
    footer = "[Esc \xAF Menu]";

    completeRender();
}

void GuiEditor::onResize()
{
    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(screenBuffer, &buffInfo);

    SetConsoleScreenBufferSize(screenBuffer, {static_cast<SHORT>(buffInfo.srWindow.Right + 1),
                                              static_cast<SHORT>(buffInfo.srWindow.Bottom + 1)});

    completeRender();
}

void GuiEditor::completeRender()
{
    //todo properly redraw the selection
    if(selectionMode)
    {
        clearSelection();
    }

    // Set the size and margins
    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(screenBuffer, &buffInfo);
    this->borderXSize = buffInfo.dwSize.X;
    this->borderYSize = buffInfo.dwSize.Y;
    topMargin = 1;
    leftMargin = 2;

    // Clear the buffer
    DWORD numChars;
    FillConsoleOutputCharacter(screenBuffer, ' ', borderXSize * borderYSize, {0, 0}, &numChars);
    FillConsoleOutputAttribute(screenBuffer, manager->getOptions().getTextColor(), borderXSize * borderYSize, {0, 0}, &numChars);

    // Draw the borders
    drawBorders(borderXSize, borderYSize);

    // Draw the header and footer
    short headerPos = (borderXSize / 2) - (header.length() / 2);
    writeString(headerPos, 0, header);
    short footerPos = (borderXSize / 2) - (footer.length() / 2);
    writeString(footerPos, borderYSize - 1, footer);

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
            line[i].Attributes = manager->getOptions().getTextColor();
        }

        // Write the line
        writeOutput(leftMargin, topMargin + currentLineNumber, line, lineLength, 1);
        if(current->getNext() == nullptr)
        {
            // If this is the last line, set the cursor to the end
            //cursorRelativeX = current->getData()->getLength();
            currentLine = current->getData();
        }
        current = current->getNext();
        currentLineNumber++;
    }

    // Set the cursor position to the end of the last line
    //cursorRelativeY = lines.getLength() - 1;
    updateCursorPos();
}

void GuiEditor::drawBorders(short newX, short newY)
{
    // Top and bottom border
    CHAR_INFO horiz[newX];
    for(int i = 1; i < newX - 1; i++)
    {
        horiz[i].Attributes = manager->getOptions().getBorderColor();
        horiz[i].Char.AsciiChar = manager->getOptions().getHorizontal();
    }
    horiz[0].Attributes = horiz[newX - 1].Attributes = manager->getOptions().getBorderColor();

    // Write with the top corners
    horiz[0].Char.AsciiChar = manager->getOptions().getTopLeftCorner();
    horiz[newX - 1].Char.AsciiChar = manager->getOptions().getTopRightCorner();
    writeOutput(0, 0, horiz, newX, 1);

    // Write with the bottom corners
    horiz[0].Char.AsciiChar = manager->getOptions().getBottomLeftCorner();
    horiz[newX - 1].Char.AsciiChar = manager->getOptions().getBottomRightCorner();
    writeOutput(0, newY - 1, horiz, newX, 1);

    // Left and right border
    CHAR_INFO vert[newY - 2];
    for(int i = 0; i < newY - 2; i++)
    {
        vert[i].Attributes = manager->getOptions().getBorderColor();
        vert[i].Char.AsciiChar = manager->getOptions().getVertical();
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
        rightWipe[i].Attributes = manager->getOptions().getTextColor();
    }
    writeOutput(borderXSize - 1, 0, rightWipe, 1, borderYSize);

    CHAR_INFO bottomWipe[borderXSize];
    for(int i = 0; i < borderXSize; i++)
    {
        bottomWipe[i].Char.AsciiChar = ' ';
        bottomWipe[i].Attributes = manager->getOptions().getTextColor();
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

COORD GuiEditor::getTextPos(COORD pos)
{
    // Generates an absolute COORD (not relative to margins) of a valid text cursor position given a COORD pos

    LinkedList<char>* target;
    COORD retPos;

    // Set the current line to the first line if the click was above the text, last line if it was below
    if(pos.Y > topMargin + lines.getLength() - 1)
    {
        target = lines.getEnd()->getData();
        retPos.Y = lines.getLength() - 1;
    }
    else if(pos.Y < topMargin)
    {
        target = lines.getStart()->getData();
        retPos.Y = 0;
    }
    else
    {
        target = lines.get(pos.Y - topMargin);
        retPos.Y = pos.Y - topMargin;
    }

    // Set the x pos to the end if the click was past the text and to the start if the click was before the text
    if(pos.X < leftMargin)
    {
        retPos.X = 0;
    }
    else if(pos.X > target->getLength() + leftMargin)
    {
        retPos.X = target->getLength();
    }
    else
    {
        retPos.X = pos.X - leftMargin;
    }

    return retPos;
}

bool GuiEditor::inSelectionRange(COORD topLeft, COORD bottomRight, COORD pos, LinkedList<char>* line)
{
    // Check if the y is in between the two
    if(topLeft.Y < pos.Y && bottomRight.Y > pos.Y)
    {
        // The whole line is selected in between lines
        return (pos.X < (line->getLength()));
    }
    else if(pos.Y == topLeft.Y)
    {
        if(topLeft.Y != bottomRight.Y)
        {
            // Only characters at or after the start are selected (if multiple lines)
            return (pos.X >= topLeft.X && pos.X <= (line->getLength()));
        }
        else
        {
            // If it's a single line, make sure it's between the bounds
            return (pos.X >= topLeft.X && pos.X <= bottomRight.X);
        }
    }
    else if(pos.Y == bottomRight.Y)
    {
        // Only the characters at or before the end are selected
        return (pos.X <= bottomRight.X);
    }
    return false;

}

SMALL_RECT GuiEditor::getBoundingBox(COORD first, COORD second)
{
    // Generates a top left and bottom right from the two coordinates
    COORD top, bottom;
    short left, right;
    if(first.Y < second.Y)
    {
        top = first;
        bottom = second;
    }
    else
    {
        top = second;
        bottom = first;
    }

    if(top.Y == bottom.Y)
    {
        left = min(top.X, bottom.X);
        right = max(top.X, bottom.X);
    }
    else
    {
        left = top.X;
        right = bottom.X;
    }

    return {left, top.Y, right, bottom.Y};
}

void GuiEditor::updateSelection(COORD start, COORD old, COORD current)
{
    // Check if the entire selection should be wiped
    bool wipe = false;
    if(current.X == -1)
    {
        wipe = true;
    }

    // Set up the bounding box to be both the old selection (so it can be cleared if it's no longer selected) and the new one
    COORD topLeftNew, bottomRightNew;
    SMALL_RECT currentRect = getBoundingBox(start, current);

    topLeftNew.X = currentRect.Left;
    topLeftNew.Y = currentRect.Top;
    bottomRightNew.X = currentRect.Right;
    bottomRightNew.Y = currentRect.Bottom;

    short startY = min(min(current.Y, start.Y), old.Y);
    short finishY = max(max(current.Y, start.Y), old.Y);

    LinkedListNode<LinkedList<char>*>* line = lines.getNode(startY);
    WORD* data;
    for(short y = startY; y <= finishY; y++)
    {
        // Write a line of attributes (size is the length of text on this line)
        data = new WORD[line->getData()->getLength()];
        for(short x = 0; x < line->getData()->getLength(); x++)
        {
            // For each x value in the line, check if it should be selected
            if(!wipe && inSelectionRange(topLeftNew, bottomRightNew, {x, y}, line->getData()))
            {
                data[x] = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
            }
            else
            {
                data[x] = manager->getOptions().getTextColor();
            }
        }

        // Output the attributes
        DWORD amount;
        COORD writePos;
        writePos.X = leftMargin;
        writePos.Y = topMargin + y;
        WriteConsoleOutputAttribute(screenBuffer, data, line->getData()->getLength(), writePos, &amount);

        // Move on to the next line
        line = line->getNext();
        delete data;
    }
}

void GuiEditor::clearSelection()
{
    // Clears the selection in memory and unrenders it
    selectionMode = false;
    updateSelection(selectionStart, selectionEnd, {-1, selectionEnd.Y});
    selectionStart = selectionEnd = lastCell = {-1, -1};
}

void GuiEditor::copySelection()
{
    string data = "";
    SMALL_RECT selection = getBoundingBox(selectionStart, selectionEnd);

    // Use a similar algorithm as the updateSelection function
    // Used to determine the range of characters that are in and out of the selection
    LinkedListNode<LinkedList<char>*>* current = lines.getNode(selection.Top);
    for(short y = selection.Top; y <= selection.Bottom; y++)
    {
        LinkedListNode<char>* currentCh = current->getData()->getStart();
        for(short x = 0; x < current->getData()->getLength(); x++)
        {
            // For each x value in the line, check if it should be selected
            if(inSelectionRange({selection.Left, selection.Top}, {selection.Right, selection.Bottom}, {x, y}, current->getData()))
            {
                data += currentCh->getData();
            }
            currentCh = currentCh->getNext();
        }
        current = current->getNext();

        // Copy a newline if at the end of a line
        if(y != selection.Bottom)
        {
            data += "\r\n";
        }
    }
    // Add a null character for clipboard compatibility
    data += '\0';

    // Copy the text to the clipboard
    OpenClipboard(nullptr);
    EmptyClipboard();
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, data.size());
    if(!hg)
    {
        CloseClipboard();
        return;
    }
    memcpy(GlobalLock(hg), data.c_str(), data.size());
    GlobalUnlock(hg);
    SetClipboardData(CF_TEXT, hg);
    CloseClipboard();
    GlobalFree(hg);
}

void GuiEditor::pasteClipboard()
{
    // Handle the clipboard api and return in the case of an error
    if(!OpenClipboard(nullptr))
    {
        return;
    }
    HANDLE hData = GetClipboardData(CF_TEXT);
    if(hData == nullptr)
    {
        return;
    }
    char * pszText = static_cast<char*>( GlobalLock(hData) );
    if(pszText == nullptr)
    {
        return;
    }
    string text(pszText);
    GlobalUnlock(hData);
    CloseClipboard();

    // Treat the clipboard data as a sequence of typed input
    for(int i = 0; i < text.length(); i++)
    {
        handleInput(text[i]);
    }
}

void GuiEditor::handleMouse(MOUSE_EVENT_RECORD m)
{
    if((m.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        // If the left mouse button is bring pressed
        // Check if it's the first press of the left mouse button (it could be an event for second button being pressed)
        if(mouseDownAt.X == -1 && mouseDownAt.Y == -1)
        {
            mouseDownAt = m.dwMousePosition;

            if(selectionMode)
            {
                clearSelection();
            }
        }

        // Set cursor pos
        COORD downText = getTextPos(m.dwMousePosition);
        cursorRelativeX = downText.X;
        cursorRelativeY = downText.Y;
        currentLine = lines.get(cursorRelativeY);
        updateCursorPos();
    }
    else
    {
        mouseDownAt = {-1, -1};
    }

    if((m.dwEventFlags & MOUSE_MOVED) == MOUSE_MOVED && mouseDownAt.X != -1 && mouseDownAt.Y != -1)
    {
        if(!selectionMode)
        {
            // Set up the selection
            selectionMode = true;
            lastCell = m.dwMousePosition;
            selectionStart = selectionEnd = getTextPos(m.dwMousePosition);
        }
        else
        {
            // Check to see if the mouse has moved cells
            if(m.dwMousePosition.X != lastCell.X || m.dwMousePosition.Y != lastCell.Y)
            {
                lastCell = m.dwMousePosition;
                // Check to see if the new textPos is different
                COORD text = getTextPos(m.dwMousePosition);
                if(text.X != selectionEnd.X || text.Y != selectionEnd.Y)
                {
                    // Update the selection
                    updateSelection(selectionStart, selectionEnd, text);
                    selectionEnd = text;
                }
            }
        }
    }
}

void GuiEditor::handleInput(int code)
{
    if(code == KEY_ENTER)
    {
        if(selectionMode)
        {
            clearSelection();
        }

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
        if(selectionMode)
        {
            clearSelection();
        }

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
    // Only print valid ascii characters (>= 32)
    else if(code >= 32)
    {
        if(selectionMode)
        {
            clearSelection();
        }

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
            ch[0].Attributes = manager->getOptions().getTextColor();
            writeOutput(leftMargin + cursorRelativeX, topMargin + cursorRelativeY, ch, 1, 1);
        }
        currentLine->add(cursorRelativeX, code);
        cursorRelativeX++;
        updateCursorPos();
    }
}

void GuiEditor::handleCtrl(int code)
{
    if(code == 'c')
    {
        if(selectionMode)
        {
            copySelection();
        }
    }
    else if(code == 'v')
    {
        pasteClipboard();
    }
    else if(code == 'a')
    {
        // Select everything
        selectionMode = true;
        selectionStart = {0, 0};
        selectionEnd.X = lines.getEnd()->getData()->getLength() - 1;
        selectionEnd.Y = lines.getLength() - 1;
        updateSelection(selectionStart, selectionEnd, selectionEnd);
    }
}

void GuiEditor::handleArrow(int code)
{
    if(selectionMode)
    {
        clearSelection();
    }

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

void GuiEditor::handleAnimationFrame(unsigned long frame)
{
    if(firstTick)
    {
        firstTick = false;
        completeRender();
    }
}