//
// Created by Techdoodle on 1/17/2019.
//

#ifndef THEEDITOR_EDITOR_H
#define THEEDITOR_EDITOR_H

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
