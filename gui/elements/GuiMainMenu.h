//
// Created by Techdoodle on 1/19/2019.
//

#ifndef THEEDITOR_GUIMAINMENU_H
#define THEEDITOR_GUIMAINMENU_H

#include "components/GuiVerticalMenu.h"
#include "components/GuiStar.h"
#include "components/comet/GuiComet.h"

#define HEADER_HEIGHT 6
#define HEADER_LENGTH 45
#define OPTIONS_LENGTH 5
#define COMETS_COUNT 3

class GuiMainMenu : public GuiFrame// : public GuiVerticalMenu
{
private:
    LinkedList<GuiStar*> stars;
    GuiComet* comets[COMETS_COUNT];

    string header[HEADER_HEIGHT];
    string tagline;
    void render();
    void cleanup();

    bool resizeIgnore = false;
    int resizeCountdown = 0;
protected:
    //void onOptionSelect(string name, int pos) override;
    void handleAnimationFrame(unsigned long count) override;
public:
    GuiMainMenu();
    ~GuiMainMenu();
    void onResize() override;
};


#endif //THEEDITOR_GUIMAINMENU_H
