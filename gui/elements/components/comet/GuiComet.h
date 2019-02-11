//
// Created by Techdoodle on 2/10/2019.
//

#ifndef THEEDITOR_GUICOMET_H
#define THEEDITOR_GUICOMET_H


#include <afxres.h>
#include "CometTrailComponent.h"

class GuiComet
{
private:
    short tailLength;
    CometTrailComponent** tail;
    HANDLE* buffer;
    bool active = false;

    // Size of screen buffer
    short xSize;
    short ySize;

    // Comet acceleration and jerk
    double xIncrease;
    double yIncrease;
    double xIncreaseFactor;
    double yIncreaseFactor;

    // Random number convenience functions
    static double genRandD(double min, double max);
    static int genRandI(int min, int max);
public:
    GuiComet(HANDLE* buffer, short xSize, short ySize);
    void animationFrame(unsigned long frame);
};


#endif //THEEDITOR_GUICOMET_H
