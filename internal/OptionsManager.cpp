//
// Created by Techdoodle on 1/18/2019.
//

#include "OptionsManager.h"
#include <fstream>
#include <windows.h>

using namespace std;

OptionsManager::OptionsManager()
{
    this->defaultOptions = Options();
    this->defaultOptions.textColor = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    this->defaultOptions.borderColor = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    this->defaultOptions.cornerColor = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    this->defaultOptions.borderType = 1;
    this->defaultOptions.cornerType = 1;

    this->loadFromFile();
}

void OptionsManager::resetToDefault()
{
    this->currentOptions = this->defaultOptions;
    this->saveToFile();
}

void OptionsManager::loadFromFile()
{
    fstream configFile(OPTIONS_FILE);
    if(!configFile)
    {
        // Some error in opening the file, likely it doesn't exist
        // Try creating the file
        this->resetToDefault();
    }
    else
    {
        string name;
        short value;
        while(configFile >> name >> value)
        {
            if(name == "border-type")
            {
                this->currentOptions.borderType = value;
            }
            else if(name == "corner-type")
            {
                this->currentOptions.cornerType = value;
            }
            else if(name == "corner-color")
            {
                this->currentOptions.cornerColor = value;
            }
            else if(name == "border-color")
            {
                this->currentOptions.borderColor = value;
            }
            else if(name == "text-color")
            {
                this->currentOptions.textColor = value;
            }
        }
        configFile.close();
    }
}

void OptionsManager::saveToFile()
{
    ofstream configFile(OPTIONS_FILE);
    configFile << "border-type " << this->currentOptions.borderType << endl;
    configFile << "corner-type " << this->currentOptions.cornerType << endl;
    configFile << "border-color " << this->currentOptions.borderColor << endl;
    configFile << "corner-color " << this->currentOptions.cornerColor << endl;
    configFile << "text-color " << this->currentOptions.textColor << endl;
    configFile.close();
}

Options OptionsManager::getOptions()
{
    return this->currentOptions;
}

void OptionsManager::setOptions(Options options)
{
    this->currentOptions = options;
    this->saveToFile();
}