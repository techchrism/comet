//
// Created by Techdoodle on 2/28/2019.
//

#ifndef COMET_GUIEDITORMENU_H
#define COMET_GUIEDITORMENU_H


#include "elements/menu/GuiVerticalMenu.h"

class GuiEditorMenu : public GuiVerticalMenu
{
private:
    void drawPreview();
    void changeSelected(int selected, int by);
protected:
    void onRender() override;
public:
    GuiEditorMenu();
    void onOptionSelect(string name, int pos) override;
    void onOptionCycle(string name, int pos, int code) override;
    void onActivate() override;
};


#endif //COMET_GUIEDITORMENU_H
