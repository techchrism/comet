//
// Created by Techdoodle on 1/18/2019.
//

#ifndef THEEDITOR_OPTIONSMANAGER_H
#define THEEDITOR_OPTIONSMANAGER_H


#include <windef.h>
#include "Options.h"

#define OPTIONS_FILE ".\\options.txt"

class OptionsManager
{
private:
    Options defaultOptions;
    Options currentOptions;

    void saveToFile();
    void loadFromFile();
public:
    OptionsManager();

    void resetToDefault();
    void setOptions(Options options);
    Options getOptions();

    unsigned char getTopLeftCorner();
    unsigned char getBottomLeftCorner();
    unsigned char getTopRightCorner();
    unsigned char getBottomRightCorner();
    unsigned char getVertical();
    unsigned char getHorizontal();
    WORD getBorderColor();
    WORD getTextColor();
};


#endif //THEEDITOR_OPTIONSMANAGER_H
