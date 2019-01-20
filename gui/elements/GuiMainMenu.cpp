//
// Created by Techdoodle on 1/19/2019.
//

#include "GuiMainMenu.h"

GuiMainMenu::GuiMainMenu()
{
    string* header = new string[1];
    header[0] = "Main Menu";

    string* options = new string[3];
    options[0] = "12345";
    options[1] = "2";
    options[2] = "asdfjhlksdf";

    this->setup(header, 1, options, 3);
}

void GuiMainMenu::onOptionSelect(string name, int pos)
{

}