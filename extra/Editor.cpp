//
// Created by Techdoodle on 1/17/2019.
//

#include "Editor.h"

Editor::Editor()
{
    rows.push(new LinkedList<char>());
    currentRow = rows.getStart()->getData();
    y = 0;
    x = 0;
}

void Editor::handleBackspace()
{
    // If we're at the start of the row, remove the enter
    if(x == 0 && y != 0)
    {
        LinkedList<char>* prev = rows.get(y - 1);
        prev->add(prev->getLength(), currentRow->getStart());
        rows.remove(y);
        y--;
        //TODO move cursor to old row
    }
    else
    {
        // Otherwise, remove the prior character
        currentRow->remove(x - 1);
        //TODO move cursor back 1
    }
}

void Editor::handleDelete()
{
    // If we're at the end of the line, remove the prior one
    if(x == currentRow->getLength())
    {
        // If there is a prior line to remove
        if((y + 1) < rows.getLength())
        {
            LinkedList<char>* next = rows.get(y + 1);
            currentRow->add(currentRow->getLength(), next->getStart());
            rows.remove(y + 1);
        }
        else
        {
            //TODO alert the user in some way
        }
    }
    else
    {
        // Otherwise, remove the current character
        currentRow->remove(x);
    }
}

void Editor::handleEnter()
{
    rows.add(y + 1, new LinkedList<char>);
    y++;
    //TODO move cursor
}

void Editor::keyPress(char code)
{

}