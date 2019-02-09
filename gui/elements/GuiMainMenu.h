//
// Created by Techdoodle on 1/19/2019.
//

#ifndef THEEDITOR_GUIMAINMENU_H
#define THEEDITOR_GUIMAINMENU_H


#include "components/GuiVerticalMenu.h"

class GuiMainMenu : public GuiVerticalMenu
{
protected:
    void onOptionSelect(string name, int pos) override;
public:
    GuiMainMenu();
};


#endif //THEEDITOR_GUIMAINMENU_H
