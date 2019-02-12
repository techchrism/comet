//
// Created by Techdoodle on 1/19/2019.
//

#include <afxres.h>
#include "GuiMainMenu.h"
#include "components/GuiMenu.h"
#include "GuiEditor.h"

GuiMainMenu::GuiMainMenu()
{
    /*string* header = new string[1];
    header[0] = "Main Menu";

    string* options = new string[3];
    options[0] = "12345";
    options[1] = "2";
    options[2] = "asdfjhlksdf";*/

    //this->setup(header, 1, options, 3);


    /*header[0] = " ██████╗ ██████╗ ███╗   ███╗███████╗████████╗";
    header[1] = "██╔════╝██╔═══██╗████╗ ████║██╔════╝╚══██╔══╝";
    header[2] = "██║     ██║   ██║██╔████╔██║█████╗     ██║   ";
    header[3] = "██║     ██║   ██║██║╚██╔╝██║██╔══╝     ██║   ";
    header[4] = "╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗   ██║   ";
    header[5] = " ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝   ╚═╝   ";*/
    header[0] = " \xDB\xDB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xBB   \xDB\xDB\xDB\xBB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB";
    header[1] = "\xDB\xDB\xC9\xCD\xCD\xCD\xCD\xBC\xDB\xDB\xC9\xCD\xCD\xCD\xDB\xDB\xBB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xDB\xBA\xDB\xDB\xC9\xCD\xCD\xCD\xCD\xBC\xC8\xCD\xCD\xDB\xDB\xC9\xCD\xCD\xBC";
    header[2] = "\xDB\xDB\xBA     \xDB\xDB\xBA   \xDB\xDB\xBA\xDB\xDB\xC9\xDB\xDB\xDB\xDB\xC9\xDB\xDB\xBA\xDB\xDB\xDB\xDB\xDB\xBB     \xDB\xDB\xBA   ";
    header[3] = "\xDB\xDB\xBA     \xDB\xDB\xBA   \xDB\xDB\xBA\xDB\xDB\xBA\xC8\xDB\xDB\xC9\xBC\xDB\xDB\xBA\xDB\xDB\xC9\xCD\xCD\xBC     \xDB\xDB\xBA   ";
    header[4] = "\xC8\xDB\xDB\xDB\xDB\xDB\xDB\xBB\xC8\xDB\xDB\xDB\xDB\xDB\xDB\xC9\xBC\xDB\xDB\xBA \xC8\xCD\xBC \xDB\xDB\xBA\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB   \xDB\xDB\xBA   ";
    header[5] = " \xC8\xCD\xCD\xCD\xCD\xCD\xBC \xC8\xCD\xCD\xCD\xCD\xCD\xBC \xC8\xCD\xBC     \xC8\xCD\xBC\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xBC   \xC8\xCD\xBC   ";

    tagline = "A command-line text editor for the stars";

    // Create the console buffer
    this->screenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
                                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                                   NULL,
                                                   CONSOLE_TEXTMODE_BUFFER,
                                                   NULL);

    // Hide cursor for menus
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = false;
    cursor.dwSize = 1;
    SetConsoleCursorInfo(this->screenBuffer, &cursor);
    render();
}

GuiMainMenu::~GuiMainMenu()
{
    cleanup();
}

void GuiMainMenu::cleanup()
{
    // Clean up the stars and the comets
    stars.removeAll();
    for(int i = 0; i < COMETS_COUNT; i++)
    {
        delete comets[i];
    }
}

/*void GuiMainMenu::onOptionSelect(string name, int pos)
{
    manager->push(new GuiEditor());
}*/

void GuiMainMenu::render()
{
    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(screenBuffer, &buffInfo);

    // Do math for centering the main menu components
    short boundingBoxHeight = HEADER_HEIGHT + OPTIONS_LENGTH + 5;
    short boundingBoxWidth = HEADER_LENGTH + 4;
    short leftX, topY, rightX, bottomY;
    leftX = (buffInfo.dwSize.X / 2) - (boundingBoxWidth / 2);
    topY = (buffInfo.dwSize.Y / 2) - (boundingBoxHeight / 2);
    rightX = leftX + boundingBoxWidth;
    bottomY = topY + boundingBoxHeight;

    // Print the header
    CHAR_INFO headerData[HEADER_LENGTH];
    for(int i = 0; i < HEADER_HEIGHT; i++)
    {
        for(int c = 0; c < HEADER_LENGTH; c++)
        {
            headerData[c].Attributes = WHITE_TEXT;
            if(header[i].length() > c)
            {
                headerData[c].Char.AsciiChar = header[i][c];
            }
            else
            {
                headerData[c].Char.AsciiChar = ' ';
            }
        }
        writeOutput(leftX + 2, topY + i + 1, headerData, HEADER_LENGTH, 1);
    }

    // Print the tagline
    int taglineOffset = (boundingBoxWidth / 2) - (tagline.length() / 2);
    CHAR_INFO taglineData[tagline.length()];
    for(int i = 0; i < tagline.length(); i++)
    {
        taglineData[i].Attributes = WHITE_TEXT;
        taglineData[i].Char.AsciiChar = tagline[i];
    }
    writeOutput(leftX + taglineOffset, topY + HEADER_HEIGHT + 2, taglineData, tagline.length(), 1);

    // Iterate through the buffer to generate stars
    int segmentXSize = 10;
    int segmentYSize = 3;

    for(short y = 0; y < buffInfo.dwSize.Y; y += segmentYSize)
    {
        for(short x = 0; x < buffInfo.dwSize.X; x += segmentXSize)
        {
            // Pick a random y and x within the screen segment
            short chosenX = x + (rand() % segmentXSize);
            short chosenY = y + (rand() % segmentYSize);

            // Skip it if it's in """the box"""
            if(chosenX >= leftX && chosenX <= rightX && chosenY >= topY && chosenY <= bottomY)
            {
                continue;
            }

            GuiStar* star = new GuiStar();
            star->setup(chosenX, chosenY, &screenBuffer);
            stars.push(star);
        }
    }

    // Initialize the comets
    for(int i = 0; i < COMETS_COUNT; i++)
    {
        comets[i] = new GuiComet(&screenBuffer, buffInfo.dwSize.X, buffInfo.dwSize.Y);
    }
}

void GuiMainMenu::onResize()
{
    // Set the buffer size and clear it
    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(screenBuffer, &buffInfo);

    SetConsoleScreenBufferSize(screenBuffer, {static_cast<SHORT>(buffInfo.srWindow.Right + 1),
                                              static_cast<SHORT>(buffInfo.srWindow.Bottom + 1)});

    short xSize = buffInfo.srWindow.Right + 1;
    short ySize = buffInfo.srWindow.Bottom + 1;
    DWORD numChars;
    FillConsoleOutputCharacter(screenBuffer, ' ', xSize * ySize, {0, 0}, &numChars);
    FillConsoleOutputAttribute(screenBuffer, WHITE_TEXT, xSize * ySize, {0, 0}, &numChars);

    // Reset and re-render the data to the new buffer dimensions
    cleanup();
    render();
}

void GuiMainMenu::handleAnimationFrame(unsigned long count)
{
    // Animate the stars
    LinkedListNode<GuiStar*>* current = stars.getStart();
    while(current != nullptr)
    {
        current->getData()->toggleChance();
        current = current->getNext();
    }

    // Animate the comets
    for(int i = 0; i < COMETS_COUNT; i++)
    {
        comets[i]->animationFrame(count);
    }
}