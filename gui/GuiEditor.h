//
// Created by Techdoodle on 1/21/2019.
//

#ifndef THEEDITOR_GUIEDITOR_H
#define THEEDITOR_GUIEDITOR_H


#include "elements/components/GuiFrame.h"

class GuiEditor : public GuiFrame
{
private:
    LinkedList<LinkedList<char>*> lines;
    LinkedList<char>* currentLine;

    string header;
    string footer;

    // The cursor position relative to the top-left margins
    // Starts at 0
    int cursorRelativeX = 0;
    int cursorRelativeY = 0;

    short borderXSize;
    short borderYSize;

    short topMargin;
    short leftMargin;

    void completeRender();
    void resizeBuffer(short newX, short newY);
    void drawBorders(short newX, short newY);
    void updateCursorPos();

    // Selection functions
    void clearSelection();
    void updateSelection(COORD start, COORD old, COORD current);
    bool inSelectionRange(COORD topLeft, COORD bottomRight, COORD pos, LinkedList<char>* line);
    SMALL_RECT getBoundingBox(COORD first, COORD second);
    void copySelection();
    void pasteClipboard();

    COORD getTextPos(COORD pos);

    COORD mouseDownAt = {-1, -1};
    COORD selectionStart = {-1, -1};
    COORD selectionEnd = {-1, -1};
    COORD lastCell = {-1, -1};
    bool selectionMode = false;
    bool firstTick = true;
public:
    GuiEditor();
    void handleArrow(int code) override;
    void handleInput(int code) override;
    void handleCtrl(int code) override;
    void handleMouse(MOUSE_EVENT_RECORD m) override;
    void handleAnimationFrame(unsigned long frame) override;
    void onResize() override;
};


#endif //THEEDITOR_GUIEDITOR_H
