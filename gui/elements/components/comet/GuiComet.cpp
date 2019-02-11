//
// Created by Techdoodle on 2/10/2019.
//

#include <afxres.h>
#include "GuiComet.h"
#include "../../../GuiFrame.h"

GuiComet::GuiComet(HANDLE *buffer, short xSize, short ySize)
{
    this->buffer = buffer;
    this->xSize = xSize;
    this->ySize = ySize;
}

double GuiComet::genRandD(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

int GuiComet::genRandI(int min, int max)
{
    return (rand() % (max - min + 1) + min);
}

void GuiComet::animationFrame(unsigned long frame)
{
    if(active)
    {
        // Set the position for the head of the comet
        yIncrease += yIncreaseFactor;
        xIncrease += xIncreaseFactor;
        double newX = tail[0]->getX() + xIncrease;
        double newY = tail[0]->getY() + yIncrease;

        // Remove the last one and move all others up
        tail[tailLength - 1]->unrender();
        delete tail[tailLength - 1];
        for(int i = tailLength - 1; i > 0; i--)
        {
            tail[i] = tail[i - 1];
        }

        // Set the new one
        tail[0] = new CometTrailComponent();
        tail[0]->setup(buffer, newX, newY, xSize, ySize);
        tail[0]->renderFront(*tail[1]);

        // Render everything else
        for(int i = 1; i < tailLength; i++)
        {
            tail[i]->renderDistance(i);
        }

        // Check if the entire comet is off-screen (done)
        bool done = true;
        for(int i = 0; i < tailLength; i++)
        {
            if(!tail[i]->isFinished())
            {
                done = false;
                break;
            }
        }
        if(done)
        {
            for(int i = 0; i < tailLength; i++)
            {
                delete tail[i];
            }
            delete tail;
            active = false;
        }
    }
    else
    {
        // 1 in 200 chance to activate
        if((rand() % 1000) < 5)
        {
            active = true;

            // Find a place on the top/left side to start from
            short pos = rand() % (xSize + ySize);
            short startX;
            short startY;
            if(pos > ySize)
            {
                // Start at the top border
                startX = pos - ySize;
                startY = 0;
            }
            else
            {
                // Start at the left border
                startX = 0;
                startY = pos;
            }

            // Determine the comet length
            tailLength = genRandI(20, 50);
            tail = new CometTrailComponent *[tailLength];
            for(int i = 0; i < tailLength; i++)
            {
                tail[i] = new CometTrailComponent();
                tail[i]->setup(buffer, startX, startY, xSize, ySize);
            }

            // Randomize the speed and speed changes (acceleration and jerk)
            xIncrease = genRandD(0.5, 1.2);
            yIncrease = genRandD(0.1, 0.3);
            xIncreaseFactor = genRandD(-0.001, 0.006);
            yIncreaseFactor = genRandD(-0.0005, 0.003);
        }
    }
}