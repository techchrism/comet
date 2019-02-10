//
// Created by Techdoodle on 2/9/2019.
//

#ifndef THEEDITOR_GUIANIMATIONTEST_H
#define THEEDITOR_GUIANIMATIONTEST_H


#include "../GuiFrame.h"

class GuiAnimationTest : public GuiFrame
{
private:

public:
    GuiAnimationTest();
    void handleAnimationFrame(int count) override;
};


#endif //THEEDITOR_GUIANIMATIONTEST_H
