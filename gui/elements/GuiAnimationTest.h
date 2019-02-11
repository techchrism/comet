//
// Created by Techdoodle on 2/9/2019.
//

#ifndef THEEDITOR_GUIANIMATIONTEST_H
#define THEEDITOR_GUIANIMATIONTEST_H


#include "../GuiFrame.h"
#include "components/GuiStar.h"

class GuiAnimationTest : public GuiFrame
{
private:
    GuiStar star;
public:
    GuiAnimationTest();
    void handleAnimationFrame(unsigned long count) override;
};


#endif //THEEDITOR_GUIANIMATIONTEST_H
