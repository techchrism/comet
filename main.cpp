#include <iostream>
#include <conio.h>

#include "internal/OptionsManager.h"
#include "gui/GuiManager.h"
#include "gui/elements/GuiBase.h"
#include "gui/elements/components/GuiMenu.h"
#include "gui/elements/GuiMainMenu.h"
#include "gui/elements/GuiEditor.h"

using namespace std;

int main()
{
    //OptionsManager options;

    // Start the GuiManager and add the current screen buffer as the root buffer
    GuiManager manager;
    manager.push(new GuiBase(GetStdHandle(STD_OUTPUT_HANDLE)));
    manager.push(new GuiEditor());

    int input = _getch();
    while(true)
    {
        if(input == 0 || input == 224)
        {
            manager.handleArrow(_getch());
        }
        else if(input == 27)
        {
            // As a means of debugging, pop the top GuiFrame off of the stack
            manager.pop();

            if(manager.getLength() == 1)
            {
                break;
            }
        }
        else
        {
            manager.handleInput(input);
        }

        input = _getch();
    }

    return 0;
}