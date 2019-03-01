//
// Created by Techdoodle on 1/18/2019.
//

#ifndef THEEDITOR_GUIMANAGER_H
#define THEEDITOR_GUIMANAGER_H

#include "../internal/LinkedList.h"
#include "../internal/OptionsManager.h"
#include "elements/components/GuiFrame.h"

// Forward definition is needed to resolve mutual dependencies
class GuiFrame;

// Manages the "stack" of gui frames and the transitions between them
class GuiManager : public InputHandler
{
private:
    LinkedList<GuiFrame*> frameStack;
    unsigned long currentCount = 0;
    HANDLE inputHandle;
    OptionsManager options;
public:
    GuiManager(OptionsManager options);
    ~GuiManager();
    OptionsManager getOptions();

    void push(GuiFrame* frame);
    void pop();
    int getLength();
    bool handleEvents();

    void handleArrow(int code) override;
    void handleInput(int code) override;
    void handleCtrl(int code) override;
    void handleAnimationFrame(unsigned long count) override;
};


#endif //THEEDITOR_GUIMANAGER_H
