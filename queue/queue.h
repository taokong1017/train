/**
 * Copyright (c) 2020-2021
 *
 * @file queue.h
 * @brief queue using list data struction
 * @version 1.0.0
 * @author wang song (taokong1017@163.com)
 * @date 2021-01-30
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include <iostream>

template<typename Item>
class Queue
{
    typedef struct Node {
        Item item;
        Node* next;
    } Node_t;
public:
    Queue( )
    : mHead(nullptr)
    , mTail(nullptr)
    , mCount(0)
    {

    }

    virtual ~Queue( ) {
        while (!empty( )){
            dequeue( );
        }
    }

    void enqueue(Item item) {
        Node_t* node = new Node_t;
        node->item = item;

        if (!mHead) {
            mHead = node;
        }
        if (mTail) {
            mTail->next = node;
        }
        mTail = node;
        mCount++;
    }

    Item dequeue( ) {
        Node_t* node = mHead;
        mHead = node->next;
        Item item = node->item;
        delete node;
        mCount--;
        return item;
    }

    size_t size( ) {
        return mCount;
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
    Node_t* mTail;
    size_t mCount;
};

#endif