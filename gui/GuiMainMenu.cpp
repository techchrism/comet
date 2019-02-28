//
// Created by Techdoodle on 1/19/2019.
//

#include <afxres.h>
#include "GuiMainMenu.h"
#include "GuiEditor.h"
#include "GuiTextBox.h"

GuiMainMenu::GuiMainMenu()
{
    /*header[0] = " ██████╗ ██████╗ ███╗   ███╗███████╗████████╗";
    header[1] = "██╔════╝██╔═══██╗████╗ ████║██╔════╝╚══██╔══╝";
    header[2] = "██║     ██║   ██║██╔████╔██║█████╗     ██║   ";
    header[3] = "██║     ██║   ██║██║╚██╔╝██║██╔══╝     ██║   ";
    header[4] = "╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗   ██║   ";
    header[5] = " ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝   ╚═╝   ";*/
    string* header = new string[6];
    header[0] = " \xDB\xDB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xBB   \xDB\xDB\xDB\xBB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB";
    header[1] = "\xDB\xDB\xC9\xCD\xCD\xCD\xCD\xBC\xDB\xDB\xC9\xCD\xCD\xCD\xDB\xDB\xBB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xDB\xBA\xDB\xDB\xC9\xCD\xCD\xCD\xCD\xBC\xC8\xCD\xCD\xDB\xDB\xC9\xCD\xCD\xBC";
    header[2] = "\xDB\xDB\xBA     \xDB\xDB\xBA   \xDB\xDB\xBA\xDB\xDB\xC9\xDB\xDB\xDB\xDB\xC9\xDB\xDB\xBA\xDB\xDB\xDB\xDB\xDB\xBB     \xDB\xDB\xBA   ";
    header[3] = "\xDB\xDB\xBA     \xDB\xDB\xBA   \xDB\xDB\xBA\xDB\xDB\xBA\xC8\xDB\xDB\xC9\xBC\xDB\xDB\xBA\xDB\xDB\xC9\xCD\xCD\xBC     \xDB\xDB\xBA   ";
    header[4] = "\xC8\xDB\xDB\xDB\xDB\xDB\xDB\xBB\xC8\xDB\xDB\xDB\xDB\xDB\xDB\xC9\xBC\xDB\xDB\xBA \xC8\xCD\xBC \xDB\xDB\xBA\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB   \xDB\xDB\xBA   ";
    header[5] = " \xC8\xCD\xCD\xCD\xCD\xCD\xBC \xC8\xCD\xCD\xCD\xCD\xCD\xBC \xC8\xCD\xBC     \xC8\xCD\xBC\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xBC   \xC8\xCD\xBC   ";

    string* options = new string[OPTIONS_LENGTH];
    options[0] = " Create New File";
    options[1] = "Open File";
    options[2] = "Quit";

    setup(header, HEADER_LENGTH, HEADER_HEIGHT, options, OPTIONS_LENGTH, 6, 0);
    render();
}

void GuiMainMenu::onRender()
{
    SMALL_RECT box = getBox();
    short lineLength = box.Right - box.Left;

    string tagline[1];
    tagline[0] = "A command-line text editor for the stars";
    CHAR_INFO* text = centerText(tagline, 1, lineLength);
    for(int i = 0; i < lineLength; i++)
    {
        text[i].Attributes = 14;
    }
    printUnderHeader(text, 0);

    tagline[0] = "\xDA Mouse Selections \xBF";
    printUnderHeader(centerText(tagline, 1, lineLength), 2);
    tagline[0] = "\xB3 Resizable Window \xB3";
    printUnderHeader(centerText(tagline, 1, lineLength), 3);
    tagline[0] = "\xC0  Fast Rendering  \xD9";
    printUnderHeader(centerText(tagline, 1, lineLength), 4);
}

void GuiMainMenu::onOptionSelect(string name, int pos)
{
    if(pos == 0)
    {
        manager->push(new GuiEditor());
    }
    else if(pos == 1)
    {
        //todo open file
        string* data = new string[3];
        data[0] = "line 1";
        data[1] = "!";
        data[2] = "AAAAAAAAAAAAAAAA 7777777777777777 BBBBB";
        manager->push(new GuiTextBox(data, 3, BACKGROUND_RED));
    }
    else if(pos == 2)
    {
        manager->pop();
    }
}

void GuiMainMenu::onOptionCycle(string name, int pos, int code)
{

}