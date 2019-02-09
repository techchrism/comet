//
// Created by Techdoodle on 1/21/2019.
//

#ifndef THEEDITOR_GUIEDITOR_H
#define THEEDITOR_GUIEDITOR_H


#include "../GuiFrame.h"

class GuiEditor : public GuiFrame
{
private:
    LinkedList<LinkedList<char>*> lines;
    LinkedList<char>* currentLine;

    // The cursor position relative to the top-left margins
    // Starts at 0
    int cursorRelativeX = 0;
    int cursorRelativeY = 0;

    short borderXSize;
    short borderYSize;

    short topMargin;
    short leftMargin;

    void completeReRender();
    void resizeBuffer(short newX, short newY);
    void resizeBorders(short oldX, short oldY, short newX, short newY);
    void printLinkedList(short x, short y, LinkedList<char> data);
    void updateCursorPos();
public:
    GuiEditor();
    void handleArrow(int code) override;
    void handleInput(int code) override;
};


#endif //THEEDITOR_GUIEDITOR_H
