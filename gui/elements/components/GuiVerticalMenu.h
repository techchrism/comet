//
// Created by Techdoodle on 1/19/2019.
//

#ifndef THEEDITOR_GUIVERTICALMENU_H
#define THEEDITOR_GUIVERTICALMENU_H


#include "../../GuiFrame.h"

class GuiVerticalMenu : public GuiFrame
{
private:
    COORD leftArrowTop;
    COORD rightArrowTop;
    void updateArrows();

protected:
    int yPos;
    string* options;
    int optionsLength;
    string* header;
    int headerLength;

    virtual void onOptionSelect(string name, int pos) = 0;
public:
    void setup(string* header, int headerLength, string* options, int optionsLength);
    void handleArrow(int code) override;
    void handleInput(int code) override;
};


#endif //THEEDITOR_GUIVERTICALMENU_H
