//
// Created by Techdoodle on 1/18/2019.
//

#ifndef THEEDITOR_OPTIONSMANAGER_H
#define THEEDITOR_OPTIONSMANAGER_H


#include "Options.h"

#define OPTIONS_FILE "options.txt"

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
};


#endif //THEEDITOR_OPTIONSMANAGER_H
