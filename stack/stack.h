/**
 * Copyright (c) 2020-2021
 *
 * @file stack.h
 * @brief stack class
 * @version 1.0.0
 * @author wang song (taokong1017@163.com)
 * @date 2021-01-30
 */
#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <iostream>

template <typename Item>
class Stack
{
    typedef struct Node {
        Item item;
        Node* next;
    } Node_t;
public:
    Stack( )
    : mHead(nullptr)
    , mCount(0)
    {

    }

    virtual ~Stack( ) {
        while (!empty( )) {
            pop( );
        }
    }

    void push(Item item) {
        mCount++;
        Node_t* node = new Node_t;
        node->item = item;
        node->next = mHead;
        mHead = node;
    }

    Item pop( ) {
        if (empty( )) {
            return Item();
        }
        mCount--;
        Node_t* first = mHead;
        mHead = mHead->next;
        Item item = first->item;
        delete first;
        return item;
    }

    bool empty( ) {
        return mCount == 0;
    }

    void dump( ) {
        Node_t* node = mHead;
        while (node) {
            std::cout << node->item << std::endl;
            node = node->next;
        }
    }

private:
    Node_t* mHead;
    size_t mCount;
};

#endif
