//
// Created by Techdoodle on 2/27/2019.
//

#ifndef COMET_GUISTARSCREEN_H
#define COMET_GUISTARSCREEN_H


#include <windows.h>
#include "../components/GuiStar.h"
#include "../../../internal/LinkedList.h"
#include "../components/comet/GuiComet.h"
#include "../components/GuiFrame.h"

#define COMETS_COUNT 4

class GuiStarScreen : public GuiFrame
{
private:
    // Volatile flags to avoid animating when deallocating memory
    volatile bool isAnimating = false;
    volatile bool isCleaning = false;

    LinkedList<GuiStar*> stars;
    GuiComet* comets[COMETS_COUNT];

    void cleanup();
protected:
    GuiStarScreen();
    ~GuiStarScreen();

    void render();
    void handleAnimationFrame(unsigned long count) override;
    void onResize() override;

    // Functions for the child elements
    virtual void childOnResize() {};
    virtual void childRender() {};
    virtual void childHandleAnimationFrame() {};
    virtual SMALL_RECT getBox() = 0;
};


#endif //COMET_GUISTARSCREEN_H
