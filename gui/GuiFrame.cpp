//
// Created by Techdoodle on 1/18/2019.
//

#include "GuiFrame.h"

void GuiFrame::setCursorPos(short x, short y)
{
    SetConsoleCursorPosition(this->screenBuffer, {x, y});
}