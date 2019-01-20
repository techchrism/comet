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
    frame->setManager(this);
    frame->onActivate();
}

void GuiManager::pop()
{
    this->frameStack.pop();
    this->frameStack.getEnd()->getData()->onActivate();
}

void GuiManager::handleArrow(int code)
{
    // Pass the arrow input to the top layer of the stack
    frameStack.getEnd()->getData()->handleArrow(code);
}

void GuiManager::handleInput(int code)
{
    frameStack.getEnd()->getData()->handleInput(code);
}

int GuiManager::getLength()
{
    return frameStack.getLength();
}