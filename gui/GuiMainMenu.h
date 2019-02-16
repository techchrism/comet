//
// Created by Techdoodle on 1/19/2019.
//

#ifndef THEEDITOR_GUIMAINMENU_H
#define THEEDITOR_GUIMAINMENU_H

#include "elements/components/GuiVerticalMenu.h"
#include "elements/components/GuiStar.h"
#include "elements/components/comet/GuiComet.h"

#define HEADER_HEIGHT 6
#define HEADER_LENGTH 45
#define OPTIONS_LENGTH 3
#define COMETS_COUNT 4

class GuiMainMenu : public GuiFrame
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

    short selectedOption = 0;
    short selectionLeftX, selectionRightX, selectionTopY;
    void renderSelection();
protected:
    void handleAnimationFrame(unsigned long count) override;
public:
    GuiMainMenu();
    ~GuiMainMenu();
    void onResize() override;
    void handleInput(int code) override;
    void handleArrow(int code) override;
};


#endif //THEEDITOR_GUIMAINMENU_H
