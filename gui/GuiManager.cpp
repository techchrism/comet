//
// Created by Techdoodle on 1/18/2019.
//

#include "GuiManager.h"

void GuiManager::push(GuiFrame* frame)
{
    this->frameStack.push(frame);
    frame->setup();
}

void GuiManager::pop()
{
    this->frameStack.pop();
}