//
// Created by Techdoodle on 2/28/2019.
//

#include <afxres.h>
#include "GuiEditorMenu.h"

GuiEditorMenu::GuiEditorMenu()
{
    /*
    ███╗   ███╗███████╗███╗   ██╗██╗   ██╗
    ████╗ ████║██╔════╝████╗  ██║██║   ██║
    ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║
    ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║
    ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝
    ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝
     */
    string* header = new string[6];
    header[0] = "\xDB\xDB\xDB\xBB   \xDB\xDB\xDB\xBB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB\xDB\xDB\xDB\xBB   \xDB\xDB\xBB\xDB\xDB\xBB   \xDB\xDB\xBB";
    header[1] = "\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xDB\xBA\xDB\xDB\xC9\xCD\xCD\xCD\xCD\xBC\xDB\xDB\xDB\xDB\xBB  \xDB\xDB\xBA\xDB\xDB\xBA   \xDB\xDB\xBA";
    header[2] = "\xDB\xDB\xC9\xDB\xDB\xDB\xDB\xC9\xDB\xDB\xBA\xDB\xDB\xDB\xDB\xDB\xBB  \xDB\xDB\xC9\xDB\xDB\xBB \xDB\xDB\xBA\xDB\xDB\xBA   \xDB\xDB\xBA";
    header[3] = "\xDB\xDB\xBA\xC8\xDB\xDB\xC9\xBC\xDB\xDB\xBA\xDB\xDB\xC9\xCD\xCD\xBC  \xDB\xDB\xBA\xC8\xDB\xDB\xBB\xDB\xDB\xBA\xDB\xDB\xBA   \xDB\xDB\xBA";
    header[4] = "\xDB\xDB\xBA \xC8\xCD\xBC \xDB\xDB\xBA\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB\xDB\xDB\xBA \xC8\xDB\xDB\xDB\xDB\xBA\xC8\xDB\xDB\xDB\xDB\xDB\xDB\xC9\xBC";
    header[5] = "\xC8\xCD\xBC     \xC8\xCD\xBC\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xBC\xC8\xCD\xBC  \xC8\xCD\xCD\xCD\xBC \xC8\xCD\xCD\xCD\xCD\xCD\xBC ";

    string* options = new string[4];
    options[0] = "Border Type";
    options[1] = "Corner Type";
    options[2] = " Border Color";
    options[3] = " Text Color";

    setup(header, 38, 6, options, 4, 0, 4);
}

void GuiEditorMenu::drawPreview()
{
    SMALL_RECT box = getBox();
    short lineLength = box.Right - box.Left;
    short previewLength = 11;
    short start = (lineLength / 2) - (previewLength / 2);

    CHAR_INFO line[lineLength];
    string text[3];
    text[0] = manager->options->getTopLeftCorner();
    text[2] = manager->options->getBottomLeftCorner();
    for(int i = 0; i < 9; i++)
    {
        text[0] += manager->options->getHorizontal();
        text[2] += manager->options->getHorizontal();
    }
    text[0] += manager->options->getTopRightCorner();
    text[2] += manager->options->getBottomRightCorner();

    text[1] = manager->options->getVertical();
    text[1] += " Preview ";
    text[1] += manager->options->getVertical();

    CHAR_INFO* topInfo = centerText(text, 3, lineLength);
    for(int i = 0; i < (lineLength * 3); i++)
    {
        if(topInfo[i].Char.AsciiChar >= 48 && topInfo[i].Char.AsciiChar <= 172)
        {
            topInfo[i].Attributes = manager->options->getTextColor();
        }
        else
        {
            topInfo[i].Attributes = manager->options->getBorderColor();
        }
    }

    printUnderOptions(topInfo, 1, 3);
}

void GuiEditorMenu::changeSelected(int selected, int by)
{
    Options options = manager->options->getOptions();
    switch(selected)
    {
        case 0:
        {
            options.borderType += by;
            if(options.borderType > 3)
            {
                options.borderType = 1;
            }
            else if(options.borderType < 1)
            {
                options.borderType = 3;
            }
            break;
        }
        case 1:
        {
            options.cornerType += by;
            if(options.cornerType > 3)
            {
                options.cornerType = 1;
            }
            else if(options.cornerType < 1)
            {
                options.cornerType = 3;
            }
            break;
        }
        case 2:
        {
            options.borderColor += by;
            if(options.borderColor > 15)
            {
                options.borderColor = 0;
            }
            else if(options.borderColor < 0)
            {
                options.borderColor = 15;
            }
            break;
        }
        case 3:
        {
            options.textColor += by;
            if(options.textColor > 15)
            {
                options.textColor = 0;
            }
            else if(options.textColor < 0)
            {
                options.textColor = 15;
            }
            break;
        }
    }
    manager->options->setOptions(options);
    drawPreview();
}

void GuiEditorMenu::onRender()
{
    drawPreview();
}

void GuiEditorMenu::onOptionSelect(string name, int pos)
{
    changeSelected(pos, 1);
}

void GuiEditorMenu::onOptionCycle(string name, int pos, int code)
{
    if(code == KEY_LEFT)
    {
        changeSelected(pos, -1);
    }
    else
    {
        changeSelected(pos, 1);
    }
}

void GuiEditorMenu::onActivate()
{
    // Set this as the active screen buffer and perform a complete re-render
    SetConsoleActiveScreenBuffer(this->screenBuffer);
    render();
}