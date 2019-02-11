//
// Created by Techdoodle on 2/10/2019.
//

#ifndef THEEDITOR_COMETTRAILCOMPONENT_H
#define THEEDITOR_COMETTRAILCOMPONENT_H


#include <winnt.h>

class CometTrailComponent
{
private:
    double x;
    double y;
    short maxX;
    short maxY;
    bool rendered = false;
    CHAR_INFO prev;
    HANDLE* buffer;

    void renderAtPos(CHAR_INFO data);
public:
    void setup(HANDLE* buffer, double x, double y, short maxX, short maxY);
    void renderFront(CometTrailComponent prev);
    void renderDistance(short distance);
    void unrender();
    bool isFinished();
    bool hasRendered();
    COORD getPos();

    double getX();
    double getY();
};


#endif //THEEDITOR_COMETTRAILCOMPONENT_H
