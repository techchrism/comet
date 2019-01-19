#include <iostream>
#include <conio.h>

#include <wchar.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h> /* included for rand */
#include <time.h>
#include <afxres.h>
#include "internal/OptionsManager.h"

using namespace std;

#define WIDTH 300
#define HEIGHT 3000

HANDLE output;

void setCursorPos(short x, short y)
{
    SetConsoleCursorPosition(output, {x, y});
}

int main(void)
{
    // Try creating a new screen buffer
    /*HANDLE startScreenBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE screenBuffer = CreateConsoleScreenBuffer(
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL
            );
    if(screenBuffer == INVALID_HANDLE_VALUE)
    {
        cout << "Could not create screen buffer ;-;" << endl;
        return 0;
    }

    SetConsoleActiveScreenBuffer(screenBuffer);
    COORD bufferSize = {WIDTH * 2, HEIGHT};
    SetConsoleScreenBufferSize(screenBuffer, bufferSize);*/

    /*output = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize = {WIDTH, HEIGHT};
    //CHAR_INFO consoleBuffer[WIDTH * HEIGHT];
    SetConsoleScreenBufferSize(output, bufferSize);

    COORD sideBufferSize = {5, HEIGHT};
    COORD bufferCoord = {0, 0};
    SMALL_RECT write_area = {0, 0, 5, HEIGHT};
    CHAR_INFO sideBuffer[5 * HEIGHT];

    for(int i = 0; i < 5 * HEIGHT; i++)
    {
        sideBuffer[i].Char.AsciiChar = '=';
        sideBuffer[i].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    }

    WriteConsoleOutput(output, sideBuffer, sideBufferSize, bufferCoord, &write_area);


    int input = _getch();
    while(input != 27)
    {
        if(input == 0 || input == 224)
        {
            switch(_getch())
            {
                case 75:
                {
                    COORD pos = {0, 0};
                    SetConsoleCursorPosition(output, pos);
                    break;
                }
                case 80:
                {
                    cout << "down ";
                    break;
                }
            }
        }
        else if(input == 8)
        {
            cout << "bs";
        }
        else
        {
            //_putch(input);
            _putch(0);
        }

        input = _getch();
    }
    //SetConsoleActiveScreenBuffer(startScreenBuffer);
    return 0;*/

    OptionsManager options;


    return 0;
}