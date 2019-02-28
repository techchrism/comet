//
// Created by Techdoodle on 1/19/2019.
//

#ifndef THEEDITOR_GUIMAINMENU_H
#define THEEDITOR_GUIMAINMENU_H

#include "elements/menu/GuiVerticalMenu.h"
#include "elements/components/GuiStar.h"
#include "elements/components/comet/GuiComet.h"
#include "elements/menu/GuiStarScreen.h"

#define HEADER_HEIGHT 6
#define HEADER_LENGTH 45
#define OPTIONS_LENGTH 3
#define COMETS_COUNT 4

class GuiMainMenu : public GuiVerticalMenu
{
protected:
    void onRender() override;
public:
    GuiMainMenu();
    void onOptionSelect(string name, int pos) override;
    void onOptionCycle(string name, int pos, int code) override;
};


#endif //THEEDITOR_GUIMAINMENU_H
