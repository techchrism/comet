//
// Created by Techdoodle on 1/19/2019.
//

#include <afxres.h>
#include "GuiMainMenu.h"
#include "GuiEditor.h"

GuiMainMenu::GuiMainMenu()
{
    /*header[0] = " ██████╗ ██████╗ ███╗   ███╗███████╗████████╗";
    header[1] = "██╔════╝██╔═══██╗████╗ ████║██╔════╝╚══██╔══╝";
    header[2] = "██║     ██║   ██║██╔████╔██║█████╗     ██║   ";
    header[3] = "██║     ██║   ██║██║╚██╔╝██║██╔══╝     ██║   ";
    header[4] = "╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗   ██║   ";
    header[5] = " ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝   ╚═╝   ";*/
    header[0] = " \xDB\xDB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xBB   \xDB\xDB\xDB\xBB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB";
    header[1] = "\xDB\xDB\xC9\xCD\xCD\xCD\xCD\xBC\xDB\xDB\xC9\xCD\xCD\xCD\xDB\xDB\xBB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xDB\xBA\xDB\xDB\xC9\xCD\xCD\xCD\xCD\xBC\xC8\xCD\xCD\xDB\xDB\xC9\xCD\xCD\xBC";
    header[2] = "\xDB\xDB\xBA     \xDB\xDB\xBA   \xDB\xDB\xBA\xDB\xDB\xC9\xDB\xDB\xDB\xDB\xC9\xDB\xDB\xBA\xDB\xDB\xDB\xDB\xDB\xBB     \xDB\xDB\xBA   ";
    header[3] = "\xDB\xDB\xBA     \xDB\xDB\xBA   \xDB\xDB\xBA\xDB\xDB\xBA\xC8\xDB\xDB\xC9\xBC\xDB\xDB\xBA\xDB\xDB\xC9\xCD\xCD\xBC     \xDB\xDB\xBA   ";
    header[4] = "\xC8\xDB\xDB\xDB\xDB\xDB\xDB\xBB\xC8\xDB\xDB\xDB\xDB\xDB\xDB\xC9\xBC\xDB\xDB\xBA \xC8\xCD\xBC \xDB\xDB\xBA\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB   \xDB\xDB\xBA   ";
    header[5] = " \xC8\xCD\xCD\xCD\xCD\xCD\xBC \xC8\xCD\xCD\xCD\xCD\xCD\xBC \xC8\xCD\xBC     \xC8\xCD\xBC\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xBC   \xC8\xCD\xBC   ";

    tagline = "A command-line text editor for the stars";

    render();
}

SMALL_RECT GuiMainMenu::getBox()
{
    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(screenBuffer, &buffInfo);

    // Do math for centering the main menu components
    short boundingBoxHeight = HEADER_HEIGHT + OPTIONS_LENGTH + 5;
    short boundingBoxWidth = HEADER_LENGTH + 4;
    SMALL_RECT ret;
    //short leftX, topY, rightX, bottomY;
    ret.Left = (buffInfo.dwSize.X / 2) - (boundingBoxWidth / 2);
    ret.Top = (buffInfo.dwSize.Y / 2) - (boundingBoxHeight / 2);
    ret.Right = ret.Left + boundingBoxWidth;
    ret.Bottom = ret.Top + boundingBoxHeight;

    return ret;
}

void GuiMainMenu::childRender()
{
    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(screenBuffer, &buffInfo);

    // Do math for centering the main menu components
    short boundingBoxHeight = HEADER_HEIGHT + OPTIONS_LENGTH + 5;
    short boundingBoxWidth = HEADER_LENGTH + 4;
    short leftX, topY, rightX, bottomY;
    leftX = (buffInfo.dwSize.X / 2) - (boundingBoxWidth / 2);
    topY = (buffInfo.dwSize.Y / 2) - (boundingBoxHeight / 2);
    rightX = leftX + boundingBoxWidth;
    bottomY = topY + boundingBoxHeight;

    // Print the header
    CHAR_INFO headerData[HEADER_LENGTH];
    for(int i = 0; i < HEADER_HEIGHT; i++)
    {
        for(int c = 0; c < HEADER_LENGTH; c++)
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
        writeOutput(leftX + 2, topY + i + 1, headerData, HEADER_LENGTH, 1);
    }

    // Print the tagline
    int taglineOffset = (boundingBoxWidth / 2) - (tagline.length() / 2);
    CHAR_INFO taglineData[tagline.length()];
    for(int i = 0; i < tagline.length(); i++)
    {
        taglineData[i].Attributes = 14;
        taglineData[i].Char.AsciiChar = tagline[i];
    }
    writeOutput(leftX + taglineOffset, topY + HEADER_HEIGHT + 2, taglineData, tagline.length(), 1);

    // Print the options
    string options[OPTIONS_LENGTH];
    options[0] = " Create New File";
    options[1] = "Open File";
    options[2] = "Quit";

    int longest = 0;
    selectionTopY = topY + HEADER_HEIGHT + 4;
    for(int i = 0; i < OPTIONS_LENGTH; i++)
    {
        if(options[i].length() > longest)
        {
            longest = options[i].length();
        }
        writeString((buffInfo.dwSize.X / 2) - (options[i].length() / 2), selectionTopY + i, options[i], 11);
    }

    selectionLeftX = (buffInfo.dwSize.X / 2) - (longest / 2) - 1;
    selectionRightX = selectionLeftX + longest + 2;

    renderSelection();
}

void GuiMainMenu::renderSelection()
{
    CHAR_INFO data[OPTIONS_LENGTH];
    for(int i = 0; i < OPTIONS_LENGTH; i++)
    {
        data[i].Char.AsciiChar = ' ';
        data[i].Attributes = WHITE_TEXT;
    }

    data[selectedOption].Attributes = 12;
    data[selectedOption].Char.AsciiChar = '>';
    writeOutput(selectionLeftX, selectionTopY, data, 1, OPTIONS_LENGTH);

    data[selectedOption].Char.AsciiChar = '<';
    writeOutput(selectionRightX, selectionTopY, data, 1, OPTIONS_LENGTH);
}

void GuiMainMenu::handleArrow(int code)
{
    if(code == KEY_DOWN)
    {
        if(selectedOption == OPTIONS_LENGTH - 1)
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
            selectedOption = OPTIONS_LENGTH - 1;
        }
        else
        {
            selectedOption--;
        }
        renderSelection();
    }
}

void GuiMainMenu::handleInput(int code)
{
    if(code == KEY_ENTER)
    {
        if(selectedOption == 0)
        {
            manager->push(new GuiEditor());
        }
        else if(selectedOption == 1)
        {
            //todo open file
        }
        else if(selectedOption == 2)
        {
            manager->pop();
        }
    }
    else if(code == KEY_ESC)
    {
        manager->pop();
    }
}