//
// Created by Techdoodle on 2/27/2019.
//

#include "GuiStarScreen.h"

GuiStarScreen::GuiStarScreen()
{
    this->screenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
                                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                                   NULL,
                                                   CONSOLE_TEXTMODE_BUFFER,
                                                   NULL);
}

GuiStarScreen::~GuiStarScreen()
{
    cleanup();
}

void GuiStarScreen::cleanup()
{
    // Delay while the animation is going
    isCleaning = true;
    while(isAnimating)
    {

    }

    stars.removeAll();
    for(int i = 0; i < COMETS_COUNT; i++)
    {
        delete comets[i];
        comets[i] = nullptr;
    }

    isCleaning = false;
}

void GuiStarScreen::render()
{
    // Hide cursor
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = false;
    cursor.dwSize = 1;
    SetConsoleCursorInfo(this->screenBuffer, &cursor);

    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(screenBuffer, &buffInfo);

    // Do math for centering the main menu components
    SMALL_RECT noStars = getBox();
    short boundingBoxHeight = noStars.Bottom - noStars.Top;
    short boundingBoxWidth = noStars.Right - noStars.Left;
    short leftX, topY, rightX, bottomY;
    leftX = (buffInfo.dwSize.X / 2) - (boundingBoxWidth / 2);
    topY = (buffInfo.dwSize.Y / 2) - (boundingBoxHeight / 2);
    rightX = leftX + boundingBoxWidth;
    bottomY = topY + boundingBoxHeight;

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

    childRender();
}

void GuiStarScreen::onResize()
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
    childOnResize();
}

void GuiStarScreen::handleAnimationFrame(unsigned long count)
{
    isAnimating = true;
    if(isCleaning)
    {
        isAnimating = false;
        return;
    }

    // Animate the stars
    LinkedListNode<GuiStar*>* current = stars.getStart();
    while(!isCleaning && current != nullptr)
    {
        current->getData()->toggleChance();
        current = current->getNext();
    }

    // Animate the comets
    for(int i = 0; i < COMETS_COUNT && !isCleaning; i++)
    {
        if(comets[i] != nullptr)
        {
            comets[i]->animationFrame(count);
        }
    }

    // Handle the optional child animation frame
    childHandleAnimationFrame();

    isAnimating = false;
}