//
// Created by Techdoodle on 1/19/2019.
//

#include <afxres.h>
#include <fstream>
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

    setup(header, HEADER_LENGTH, HEADER_HEIGHT, options, OPTIONS_LENGTH, 7, 0);
    render();
}

void GuiMainMenu::onRender()
{
    SMALL_RECT box = getBox();
    short lineLength = box.Right - box.Left;

    printUnderHeader(setColor(centerText("A command-line text editor for the stars", lineLength), lineLength, 14), 0);

    printUnderHeader(centerText("\xDA Mouse Selections \xBF", lineLength), 2);
    printUnderHeader(centerText("\xB3 Resizable Window \xB3", lineLength), 3);
    printUnderHeader(centerText("\xB3  Saved Options   \xB3", lineLength), 4);
    printUnderHeader(centerText("\xC0  Fast Rendering  \xD9", lineLength), 5);
}

void GuiMainMenu::onOptionSelect(string name, int pos)
{
    if(pos == 0)
    {
        manager->push(new GuiEditor());
    }
    else if(pos == 1)
    {
        // Try opening the file
        ifstream fstr;
        fstr.open("./saved.txt");
        if(!fstr.is_open())
        {
            // Show error message
            string* data = new string[6];
            data[0] = "Error";
            data[1] = "";
            data[2] = "File \"saved.txt\" could not be opened";
            data[3] = "(Does it exist?)";
            data[4] = "";
            data[5] = "Press any key to return";
            manager->push(new GuiTextBox(data, 6, BACKGROUND_RED));
        }
        else
        {
            manager->push(new GuiEditor(fstr));
        }
    }
    else if(pos == 2)
    {
        manager->pop();
    }
}

void GuiMainMenu::onOptionCycle(string name, int pos, int code)
{

}