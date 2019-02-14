//
// Created by Techdoodle on 2/11/2019.
//

#ifndef COMET_GUIBASE_H
#define COMET_GUIBASE_H


#include <windows.h>
#include "elements/components/GuiFrame.h"

class GuiBase : public GuiFrame
{
public:
    GuiBase(HANDLE buffer);
};


#endif //COMET_GUIBASE_H
