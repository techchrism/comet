//
// Created by Techdoodle on 1/18/2019.
//

#ifndef THEEDITOR_GUIMENU_H
#define THEEDITOR_GUIMENU_H


#include "../../GuiFrame.h"

class GuiMenu : public GuiFrame
{
public:
    GuiMenu();

    void handleInput(int code) override;
    void handleArrow(int code) override;
};


#endif //THEEDITOR_GUIMENU_H
