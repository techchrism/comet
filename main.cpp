#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "internal/OptionsManager.h"
#include "gui/GuiManager.h"
#include "gui/elements/components/GuiMenu.h"
#include "gui/GuiMainMenu.h"
#include "gui/GuiEditor.h"
#include "gui/GuiBase.h"

using namespace std;

DWORD WINAPI thread_func(LPVOID lpParameter)
{
    GuiManager* gui = (GuiManager*) lpParameter;

    DWORD ticks = GetTickCount();
    while(gui->getLength() > 1)
    {
        DWORD currentTicks = GetTickCount();
        if(currentTicks - ticks >= 1)
        {
            gui->handleAnimationFrame(0);
            ticks = currentTicks;
        }
        Sleep(1);
    }
    return 0;
}

int main()
{
    //OptionsManager options;

    // Save the old title to be restored after the application closes
    TCHAR oldTitle[MAX_PATH];
    GetConsoleTitle(oldTitle, MAX_PATH);

    // Seed random numbers with the current time
    srand(time(0));

    SetConsoleTitle("Comet Editor");

    // Start the GuiManager and add the current screen buffer as the root buffer
    GuiManager manager;
    manager.push(new GuiBase(GetStdHandle(STD_OUTPUT_HANDLE)));
    manager.push(new GuiMainMenu());
    manager.push(new GuiEditor());

    // Start animation worker thread
    CreateThread(nullptr, 0, thread_func, &manager, 0, nullptr);

    // Trigger event loop
    while(manager.handleEvents())
    {

    }

    // Restore the starting title
    SetConsoleTitle(oldTitle);
    return 0;
}