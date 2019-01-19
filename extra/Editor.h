//
// Created by Techdoodle on 1/17/2019.
//

#ifndef THEEDITOR_EDITOR_H
#define THEEDITOR_EDITOR_H

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define KEY_BACKSPACE 8
#define KEY_DELETE 127

#include "../internal/LinkedList.h"

class Editor
{
private:
    LinkedList<LinkedList<char>*> rows;
    LinkedList<char>* currentRow;
    int y;
    int x;

    int actualCursorPos = 0;
    void moveCursor(int id);

    void handleBackspace();
    void handleDelete();
    void handleEnter();

    void reRender();
public:
    Editor();

    void arrowPress(char code);
    void keyPress(char code);
};


#endif //THEEDITOR_EDITOR_H
