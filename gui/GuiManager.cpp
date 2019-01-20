//
// Created by Techdoodle on 1/18/2019.
//

#include "GuiManager.h"

GuiManager::GuiManager()
{

}

GuiManager::~GuiManager()
{
    this->frameStack.removeAll();
}

// Push and activate the new frame
void GuiManager::push(GuiFrame* frame)
{
    this->frameStack.push(frame);
    //frame->setManager(this);
    frame->onActivate();
}

void GuiManager::pop()
{
    this->frameStack.pop();
    this->frameStack.getEnd()->getData()->onActivate();
}