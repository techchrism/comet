//
// Created by Techdoodle on 1/19/2019.
//

#ifndef THEEDITOR_GUIVERTICALMENU_H
#define THEEDITOR_GUIVERTICALMENU_H


#include "../components/GuiFrame.h"
#include "GuiStarScreen.h"

class GuiVerticalMenu : public GuiStarScreen
{
private:
    string* header;
    int headerLength;
    int headerHeight;

    string* options;
    int optionsLength;

    short spaceAfterHeader;
    short spaceAfterOptions;

    short selectedOption = 0;
    short selectionLeftX, selectionRightX, selectionTopY;
    short posAfterHeader;
    short posAfterOptions;

    void renderSelection();
    void renderOptions();

protected:
    SMALL_RECT getBox() override;
    void childRender() override;
    void setOption(int pos, string replacement);

    virtual void onRender() {};
    virtual void onOptionSelect(string name, int pos) = 0;
    virtual void onOptionCycle(string name, int pos, int code) = 0;

    void printUnderHeader(CHAR_INFO* data, short yPos);
    void printUnderOptions(CHAR_INFO* data, short yPos);
public:
    void setup(string* header, int headerLength, int headerHeight, string* options, int optionsLength, short spaceAfterHeader, short spaceAfterOptions);
    void handleArrow(int code) override;
    void handleInput(int code) override;
};


#endif //THEEDITOR_GUIVERTICALMENU_H
