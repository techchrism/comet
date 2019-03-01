//
// Created by Techdoodle on 1/18/2019.
//

#include <afxres.h>
#include "GuiManager.h"
#include "../internal/OptionsManager.h"

GuiManager::GuiManager()
{
    this->options = new OptionsManager();

    inputHandle = GetStdHandle(STD_INPUT_HANDLE);

    // Disable the windows "Quick Edit Mode" that creates a selection box when the mouse is clicked and dragged
    // Also disable the CTRL + C break command
    DWORD prev_mode;
    GetConsoleMode(inputHandle, &prev_mode);
    SetConsoleMode(inputHandle, prev_mode & ~ENABLE_QUICK_EDIT_MODE & ~ENABLE_PROCESSED_INPUT);
}

GuiManager::~GuiManager()
{
    this->frameStack.removeAll();
    delete this->options;
}

// Push and activate the new frame
void GuiManager::push(GuiFrame* frame)
{
    currentCount = 0;
    frame->setManager(this);
    this->frameStack.push(frame);
    frame->onActivate();
}

void GuiManager::pop()
{
    currentCount = 0;
    this->frameStack.pop();
    this->frameStack.getEnd()->getData()->onActivate();
}

bool GuiManager::handleEvents()
{
    // Get console events (blocking operation)
    DWORD numRead;
    INPUT_RECORD inBuf[128];
    ReadConsoleInput(inputHandle, inBuf, 128, &numRead);

    // Iterate through the events
    for(int i = 0; i < numRead; i++)
    {
        switch(inBuf[i].EventType)
        {
            case KEY_EVENT:
            {
                // If it's a keyboard event, handle it
                KEY_EVENT_RECORD ev = inBuf[i].Event.KeyEvent;
                DWORD vk = ev.wVirtualKeyCode;
                if(ev.bKeyDown)
                {
                    // Check if the ctrl key is pressed
                    if(((ev.dwControlKeyState & LEFT_CTRL_PRESSED) == LEFT_CTRL_PRESSED ||
                        (ev.dwControlKeyState & RIGHT_CTRL_PRESSED) == RIGHT_CTRL_PRESSED)
                        && vk != VK_CONTROL)
                    {
                        // Sends 1 for a, 2-b, 3-c, ect.
                        // Add 96 to convert to proper ascii
                        handleCtrl(ev.uChar.AsciiChar + 96);
                    }
                    else if(vk == VK_LEFT || vk == VK_RIGHT || vk == VK_UP || vk == VK_DOWN)
                    {
                        handleArrow(vk);
                    }
                    else
                    {
                        handleInput(ev.uChar.AsciiChar);
                    }
                }
                break;
            }
            case WINDOW_BUFFER_SIZE_EVENT:
            {
                // Handle window resize events
                frameStack.getEnd()->getData()->onResize();
                break;
            }
            case MOUSE_EVENT:
            {
                frameStack.getEnd()->getData()->handleMouse(inBuf[i].Event.MouseEvent);
            }
            default:
            {
                break;
            }
        }
    }
    return (frameStack.getLength() != 1);
}

void GuiManager::handleArrow(int code)
{
    // Pass the arrow input to the top layer of the stack
    frameStack.getEnd()->getData()->handleArrow(code);
}

void GuiManager::handleAnimationFrame(unsigned long count)
{
    currentCount++;
    frameStack.getEnd()->getData()->handleAnimationFrame(currentCount);
}

void GuiManager::handleInput(int code)
{
    frameStack.getEnd()->getData()->handleInput(code);
}

void GuiManager::handleCtrl(int code)
{
    frameStack.getEnd()->getData()->handleCtrl(code);
}

int GuiManager::getLength()
{
    return frameStack.getLength();
}