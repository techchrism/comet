//
// Created by Techdoodle on 1/19/2019.
//

#ifndef THEEDITOR_GUIMAINMENU_H
#define THEEDITOR_GUIMAINMENU_H

#include "elements/components/GuiVerticalMenu.h"
#include "elements/components/GuiStar.h"
#include "elements/components/comet/GuiComet.h"
#include "elements/menu/GuiStarScreen.h"

#define HEADER_HEIGHT 6
#define HEADER_LENGTH 45
#define OPTIONS_LENGTH 3
#define COMETS_COUNT 4

class GuiMainMenu : public GuiStarScreen
{
private:
    string header[HEADER_HEIGHT];
    string tagline;
    void childRender() override;

    short selectedOption = 0;
    short selectionLeftX, selectionRightX, selectionTopY;
    void renderSelection();

protected:
    virtual SMALL_RECT getBox() override;
public:
    GuiMainMenu();
    void handleInput(int code) override;
    void handleArrow(int code) override;
};


#endif //THEEDITOR_GUIMAINMENU_H
