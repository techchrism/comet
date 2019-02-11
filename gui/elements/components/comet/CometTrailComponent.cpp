//
// Created by Techdoodle on 2/10/2019.
//

#include <afxres.h>
#include <cmath>
#include "CometTrailComponent.h"

void CometTrailComponent::setup(HANDLE *buffer, double x, double y, short maxX, short maxY)
{
    this->buffer = buffer;
    this->maxX = maxX;
    this->maxY = maxY;

    this->x = x;
    this->y = y;
}

COORD CometTrailComponent::getPos()
{
    COORD pos;
    pos.X = round(x);
    pos.Y = round(y);
    return pos;
}

double CometTrailComponent::getX()
{
    return x;
}

double CometTrailComponent::getY()
{
    return y;
}

bool CometTrailComponent::isFinished()
{
    return (round(x) > maxX || round(y) > maxY);
}

bool CometTrailComponent::hasRendered()
{
    return rendered;
}

void CometTrailComponent::renderFront(CometTrailComponent prev)
{
    if(isFinished())
    {
        return;
    }
    COORD pos = getPos();
    COORD prevPos = prev.getPos();

    // If the previous tail component has already rendered here, don't bother
    if(pos.X == prevPos.X && pos.Y == prevPos.Y)
    {
        rendered = false;
    }
    else
    {
        // Check the character at the proposed rendering position
        CHAR_INFO c;
        SMALL_RECT box = {pos.X, pos.Y, static_cast<SHORT>(pos.X + 1), static_cast<SHORT>(pos.Y + 1)};
        ReadConsoleOutput(*buffer, &c, {1, 1}, {0, 0}, &box);

        char k = c.Char.AsciiChar;
        // Allow the comet to pass over stars and empty spaces
        if(k == '*' || k == ' ')
        {
            rendered = true;
            this->prev = c;
            renderDistance(0);
        }
        else
        {
            rendered = false;
        }
    }
}

void CometTrailComponent::unrender()
{
    if(isFinished())
    {
        return;
    }

    if(rendered)
    {
        // Reset to the character that was previously there
        renderAtPos(prev);
    }
}

void CometTrailComponent::renderAtPos(CHAR_INFO data)
{
    CHAR_INFO display[1];
    display[0] = data;
    COORD pos = getPos();
    SMALL_RECT box = {pos.X, pos.Y, static_cast<SHORT>(pos.X + 1), static_cast<SHORT>(pos.Y + 1)};
    WriteConsoleOutput(*buffer, display, {1, 1}, {0, 0}, &box);
}

void CometTrailComponent::renderDistance(short distance)
{
    if(isFinished())
    {
        return;
    }

    if(!rendered)
    {
        return;
    }

    // Render the comet component differently depending on its distance from the head
    CHAR_INFO data;
    if(distance <= 1)
    {
        data.Attributes = 11;
        data.Char.AsciiChar = 'O';
    }
    else if(distance <= 8)
    {
        data.Attributes = 3;
        data.Char.AsciiChar = '"';
    }
    else if(distance <= 15)
    {
        data.Attributes = 1;
        data.Char.AsciiChar = (unsigned char) '\'';
    }
    else
    {
        data.Attributes = 8;
        data.Char.AsciiChar = (unsigned char) '\'';
    }

    renderAtPos(data);
}