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
    configFile << "text-color " << this->currentOptions.textColor << endl;
    configFile.close();
}

Options OptionsManager::getOptions()
{
    return this->currentOptions;
}

void OptionsManager::setOptions(Options options)
{
    this->currentOptions.borderColor = options.borderColor;
    this->currentOptions.borderType = options.borderType;
    this->currentOptions.cornerType = options.cornerType;
    this->currentOptions.textColor = options.textColor;
    this->saveToFile();
}

unsigned char OptionsManager::getTopLeftCorner()
{
    if(this->currentOptions.cornerType == 1)
    {
        return (unsigned char) 201;
    }
    else if(this->currentOptions.cornerType == 2)
    {
        return (unsigned char) 218;
    }
    else
    {
        return '+';
    }
}

unsigned char OptionsManager::getTopRightCorner()
{
    if(currentOptions.cornerType == 1)
    {
        return (unsigned char) 187;
    }
    else if(currentOptions.cornerType == 2)
    {
        return (unsigned char) 191;
    }
    else
    {
        return '+';
    }
}

unsigned char OptionsManager::getBottomLeftCorner()
{
    if(currentOptions.cornerType == 1)
    {
        return (unsigned char) 200;
    }
    else if(currentOptions.cornerType == 2)
    {
        return (unsigned char) 192;
    }
    else
    {
        return '+';
    }
}

unsigned char OptionsManager::getBottomRightCorner()
{
    if(currentOptions.cornerType == 1)
    {
        return (unsigned char) 188;
    }
    else if(currentOptions.cornerType == 2)
    {
        return (unsigned char) 217;
    }
    else
    {
        return '+';
    }
}

unsigned char OptionsManager::getHorizontal()
{
    if(currentOptions.borderType == 1)
    {
        return (unsigned char) 205;
    }
    else if(currentOptions.borderType == 2)
    {
        return (unsigned char) 196;
    }
    else
    {
        return (unsigned char) 219;
    }
}

unsigned char OptionsManager::getVertical()
{
    if(currentOptions.borderType == 1)
    {
        return (unsigned char) 186;
    }
    else if(currentOptions.borderType == 2)
    {
        return (unsigned char) 179;
    }
    else
    {
        return (unsigned char) 219;
    }
}

WORD OptionsManager::getBorderColor()
{
    return currentOptions.borderColor;
}

WORD OptionsManager::getTextColor()
{
    return currentOptions.textColor;
}