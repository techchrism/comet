//
// Created by Techdoodle on 1/19/2019.
//

#include <afxres.h>
#include "GuiVerticalMenu.h"

void GuiVerticalMenu::setup(string *header, int headerLength, int headerHeight, string *options, int optionsLength,
                            short spaceAfterHeader, short spaceAfterOptions)
{
    this->header = header;
    this->headerLength = headerLength;
    this->headerHeight = headerHeight;
    this->options = options;
    this->optionsLength = optionsLength;
    this->spaceAfterHeader = spaceAfterHeader;
    this->spaceAfterOptions = spaceAfterOptions;
}

SMALL_RECT GuiVerticalMenu::getBox()
{
    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(screenBuffer, &buffInfo);

    // Do math for centering the main menu components
    short boundingBoxHeight = 1 + headerHeight + 1 + spaceAfterHeader + optionsLength + 1 + spaceAfterOptions;
    short boundingBoxWidth = headerLength + 4;
    SMALL_RECT ret;
    ret.Left = (buffInfo.dwSize.X / 2) - (boundingBoxWidth / 2);
    ret.Top = (buffInfo.dwSize.Y / 2) - (boundingBoxHeight / 2);
    ret.Right = ret.Left + boundingBoxWidth;
    ret.Bottom = ret.Top + boundingBoxHeight;

    return ret;
}

void GuiVerticalMenu::childRender()
{
    SMALL_RECT box = getBox();

    // Print the header
    CHAR_INFO headerData[headerLength];
    for(int i = 0; i < headerHeight; i++)
    {
        for(int c = 0; c < headerLength; c++)
        {
            if(header[i][c] == (char) 219)
            {
                headerData[c].Attributes = 11;
            }
            else if(header[i][c] == ' ')
            {
                headerData[c].Attributes = WHITE_TEXT;
            }
            else
            {
                headerData[c].Attributes = 9;
            }

            if(header[i].length() > c)
            {
                headerData[c].Char.AsciiChar = header[i][c];
            }
            else
            {
                headerData[c].Char.AsciiChar = ' ';
            }
        }
        writeOutput(box.Left + 2, box.Top + i + 1, headerData, headerLength, 1);
    }
    posAfterHeader = box.Top + 1 + headerHeight + 1;

    renderOptions();
    onRender();
}

void GuiVerticalMenu::setOption(int pos, string replacement)
{
    options[pos] = replacement;
    renderOptions();
}

void GuiVerticalMenu::renderOptions()
{
    SMALL_RECT box = getBox();
    int longest = 0;
    selectionTopY = box.Top + 1 + headerHeight + 1 + spaceAfterHeader;
    for(int i = 0; i < optionsLength; i++)
    {
        if(options[i].length() > longest)
        {
            longest = options[i].length();
        }
        writeString(((box.Right - box.Left) / 2) - (options[i].length() / 2) + box.Left, selectionTopY + i, options[i], 11);
    }
    posAfterOptions = box.Top + 1 + headerHeight + 1 + spaceAfterHeader + optionsLength;

    selectionLeftX = ((box.Right - box.Left) / 2) - (longest / 2) - 1 + box.Left;
    selectionRightX = selectionLeftX + longest + 2;
    renderSelection();
}

void GuiVerticalMenu::printUnderHeader(CHAR_INFO *data, short yPos)
{
    SMALL_RECT box = getBox();
    short boxGap = box.Right - box.Left;
    writeOutput(box.Left, posAfterHeader + yPos, data, boxGap, 1);
    delete data;
}

void GuiVerticalMenu::printUnderOptions(CHAR_INFO *data, short yPos)
{
    SMALL_RECT box = getBox();
    short boxGap = box.Right - box.Left;
    writeOutput(box.Left, posAfterOptions + yPos, data, boxGap, 1);
    delete data;
}

void GuiVerticalMenu::renderSelection()
{
    CHAR_INFO data[optionsLength];
    for(int i = 0; i < optionsLength; i++)
    {
        data[i].Char.AsciiChar = ' ';
        data[i].Attributes = WHITE_TEXT;
    }

    data[selectedOption].Attributes = 12;
    data[selectedOption].Char.AsciiChar = '>';
    writeOutput(selectionLeftX, selectionTopY, data, 1, optionsLength);

    data[selectedOption].Char.AsciiChar = '<';
    writeOutput(selectionRightX, selectionTopY, data, 1, optionsLength);
}

void GuiVerticalMenu::handleArrow(int code)
{
    if(code == KEY_DOWN)
    {
        if(selectedOption == optionsLength - 1)
        {
            selectedOption = 0;
        }
        else
        {
            selectedOption++;
        }
        renderSelection();
    }
    else if(code == KEY_UP)
    {
        if(selectedOption == 0)
        {
            selectedOption = optionsLength - 1;
        }
        else
        {
            selectedOption--;
        }
        renderSelection();
    }
    else
    {
        onOptionCycle(options[selectedOption], selectedOption, code);
    }
}

void GuiVerticalMenu::handleInput(int code)
{
    if(code == KEY_ENTER)
    {
        onOptionSelect(options[selectedOption], selectedOption);
    }
}