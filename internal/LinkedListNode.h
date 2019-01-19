//
// Created by Techdoodle on 1/17/2019.
//

#ifndef THEEDITOR_LINKEDLISTNODE_H
#define THEEDITOR_LINKEDLISTNODE_H

template <typename T>
class LinkedListNode
{
private:
    LinkedListNode<T>* next;
    T data;
public:
    LinkedListNode()
    {
        this->next = nullptr;
    }

    LinkedListNode(T data)
    {
        this->next = nullptr;
        this->data = data;
    }

    void setData(T data)
    {
        this->data = data;
    }

    T getData()
    {
        return this->data;
    }

    void setNext(LinkedListNode<T>* next)
    {
        this->next = next;
    }

    LinkedListNode<T>* getNext()
    {
        return this->next;
    }
};


#endif //THEEDITOR_LINKEDLISTNODE_H
