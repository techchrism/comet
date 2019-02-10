//
// Created by Techdoodle on 1/18/2019.
//

#ifndef THEEDITOR_GUIMANAGER_H
#define THEEDITOR_GUIMANAGER_H

#include "../internal/LinkedList.h"
#include "GuiFrame.h"

// Forward definition is needed to resolve mutual dependencies
class GuiFrame;

// Manages the "stack" of gui frames and the transitions between them
class GuiManager : public InputHandler
{
private:
    LinkedList<GuiFrame*> frameStack;
    int currentCount = 0;
public:
    GuiManager();
    ~GuiManager();

    void push(GuiFrame* frame);
    void pop();
    int getLength();

    void handleArrow(int code) override;
    void handleInput(int code) override;
    void handleAnimationFrame(int count) override;
};


#endif //THEEDITOR_GUIMANAGER_H
