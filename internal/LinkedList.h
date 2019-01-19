//
// Created by Techdoodle on 1/17/2019.
//

#ifndef THEEDITOR_LINKEDLIST_H
#define THEEDITOR_LINKEDLIST_H

#include "LinkedListNode.h"

template <typename T>
class LinkedList
{
private:
    LinkedListNode<T>* start;
    LinkedListNode<T>* end;
    int length;
public:
    LinkedList()
    {
        this->start = nullptr;
        this->end = nullptr;
        this->length = 0;
    }

    LinkedListNode<T>* getStart()
    {
        return this->start;
    }

    LinkedListNode<T>* getEnd()
    {
        return this->end;
    }

    void push(T data)
    {
        this->add(this->length, data);
    }

    void pop()
    {
        this->remove(this->length - 1);
    }

    void removeAll()
    {
        // Remove all nodes
        while(this->start != nullptr)
        {
            LinkedListNode<T>* removed = this->start;
            this->start = this->start->getNext();
            delete removed;
        }
        this->end = nullptr;

        this->length = 0;
    }

    void remove(int pos)
    {
        // Check to make sure there are items to remove
        if(this->length == 0)
        {
            return;
        }

        if(pos == 0)
        {
            // Special case for moving the start pointer
            LinkedListNode<T>* removed = this->start;
            this->start = this->start->getNext();
            delete removed;
            length--;

            // If the element removed was the last one in the list, set the end pointer to the start
            // (both should now be nullptr)
            if(length == 0)
            {
                this->end = this->start;
            }
        }
        else
        {
            // Continue through the list until the spot is found
            LinkedListNode<T>* current = this->start;
            int currentPos = 0;
            while(current->getNext() != nullptr)
            {
                // We want the element before the one being removed so we can readdress the next pointer
                if(currentPos == (pos - 1))
                {
                    LinkedListNode<T>* removed = current->getNext();
                    current->setNext(removed->getNext());
                    delete removed;

                    // If we removed the last element, redirect the end pointer
                    if(current->getNext() == nullptr)
                    {
                        this->end = current;
                    }

                    length--;
                    break;
                }

                current = current->getNext();
                currentPos++;
            }
            // Note: There are no errors thrown if pos is invalid
        }
    }

    void add(int pos, T data)
    {
        this->add(pos, new LinkedListNode<T>(data));
    }

    void add(int pos, LinkedListNode<T>* data)
    {
        LinkedListNode<T>* last;

        // Measure the length of added data and set the "last" pointer to the end of it
        int count = 0;
        LinkedListNode<T>* temp = data;
        while(temp != nullptr)
        {
            count++;
            if(temp->getNext() == nullptr)
            {
                last = temp;
            }
            temp = temp->getNext();
        }

        // If the linked list is empty, add this as the first
        if(this->start == nullptr)
        {
            this->start = data;
            this->end = last;
            this->length += count;
        }
        else if(pos == 0)
        {
            // Special case for moving the start pointer
            last->setNext(this->start);
            this->start = data;
            this->length += count;
        }
        else if(pos == this->length)
        {
            // Special case for moving the end pointer
            this->end->setNext(data);
            this->end = last;
            this->length += count;
        }
        else
        {
            // Otherwise, continue through the linked list until we reach the spot
            int currentPos = 1;
            LinkedListNode<T>* current = this->start;
            while(current != nullptr)
            {
                if(currentPos == pos)
                {
                    // If we're at the right position, add the node
                    last->setNext(current->getNext());
                    current->setNext(data);
                    this->length += count;
                    break;
                }

                currentPos++;
                current = current->getNext();
            }
            // Note: if the spot isn't reached or is otherwise invalid (negative), no errors are thrown
        }
    }

    T get(int pos)
    {
        // Optimization for first item
        if(pos == 0)
        {
            return this->start->getData();
        }

        // Optimization for last item
        if(pos == (this->length - 1))
        {
            return this->end->getData();
        }

        int currentPos = 0;
        LinkedListNode<T>* current = this->start;
        while(current != nullptr)
        {
            if(currentPos == pos)
            {
                return current->getData();
            }

            currentPos++;
            current = current->getNext();
        }
        return nullptr;
    }

    int getLength()
    {
        return this->length;
    }
};


#endif //THEEDITOR_LINKEDLIST_H
