#include <iostream>
#include <algorithm>
#include "avltree.h"

template <typename T>
AvlTree<T>::AvlTree()
    : mRoot(nullptr)
{

}

template <typename T>
AvlTree<T>::AvlTree(const std::vector<T>& list)
    : mRoot(nullptr)
{
    for(const auto& data : list) {
        addNode(data);
    }
}

template <typename T>
void AvlTree<T>::addNode(const T& data)
{
    mRoot = insertNode<T>(mRoot, data);
}

template <typename T>
void AvlTree<T>::printOrderTree()
{
    printOrderTree<T>(mRoot);
}

template <typename T>
Node<T>* AvlTree<T>::newNode(const T& data,  Node<T>* lchild, Node<T>* rchild, size_t height)
{
    Node<T>* node = new Node<T>();
    if(node) {
        node->value = data;
        node->height = height;
        node->lChild = lchild;
        node->rChlid = rchild;
    }
    return node;
}

/*
*            k1                    k2
*          /    \                /    \
*        k2       c    ==>      a      k1
*       /   \                        /    \
*      a     b                      b      c    
*/
template <typename T>
Node<T>* AvlTree<T>::rightRightRotate(Node<T>* k1)
{
    Node<T>* k2 = k1->lChild;
    k1->lChild = k2->rChlid;
    k2->rChlid = k1;
    k1->height = std::max<int>(height<T>(k1->lChild), height<T>(k1->rChlid)) + 1;
    k2->height = std::max<int>(height<T>(k2->lChild), height<T>(k2->rChlid)) + 1;
    return k2;
}

/*
*         k1                         k2
*       /    \                     /    \
*      a      k2     ==>         k1      c
*           /    \             /    \
*          b      c          a       b  
*/
template <typename T>
Node<T>* AvlTree<T>::leftLeftRotate(Node<T>* k1)
{
    Node<T>* k2 = k1->rChild;
    k1->rChlid = k2->lChild;
    k2->lChild = k1;
    k1->height = std::max<int>(height<T>(k1->lChild), height<T>(k1->rChlid)) + 1;
    k2->height = std::max<int>(height<T>(k2->lChild), height<T>(k2->rChlid)) + 1;
    return k2;
}

/*
 *               k1                  k1                      k3
 *             /   \               /    \                  /    \
 *           k2     d            k3      d               k2      k1
 *         /   \                /  \                   /    \   /   \
 *        a     k3       ==>  k2    c           ==>   a      b c     d
 *             /  \         /   \
 *            b    c       a     b
*/
template <typename T>
Node<T>* AvlTree<T>::leftRightRotate(Node<T>* k1)
{
    k1->lChild = leftLeftRotate<T>(k1->lChild);
    return rightRightRotate<T>(k1);
}

/**
 *             k1                  k1                           k3
 *           /   \                /   \                       /    \
 *         a       k2      ==>   a     k3         ==>       k1      k2
 *               /   \               /    \               /    \   /  \
 *             k3     d             b      k2            a      b c     d
 *           /   \                       /    \
 *          b      c                    c       d
*/
template <typename T>
Node<T>* AvlTree<T>::rightLeftRotate(Node<T>* k1)
{
    k1->rChlid = rightRightRotate<T>(k1->rChlid);
    return leftLeftRotate<T>(k1);
}

template <typename T>
Node<T>* insertNode(Node<T>* root, const T& data)
{
    /* add new node*/
    if(!root) {
        return root = newNode<T>(data);
    } else if(data < root->value) {
        return root->lChild = insertNode<T>(root->lChild, data);
    } else {
        return root->rChild = insertNode<T>(root->rChlid, data);
    }

    /* adjust avl tree heigh, difference less than 2*/
    int lheight = height<T>(root->lChild);
    int rheight = height<T>(root->rChild);
    if (lheight - rheight >= 2) {
        if (data < root->lChild->value) {
            rightRightRotate<T>(root);
        } else {
            leftRightRotate<T>(root);
        }
    }
    if(rheight - lheight >= 2) {
        if (data < root->rChild->value) {
            rightLeftRotate<T>(root);
        } else {
            leftLeftRotate<T>(root);
        }
    }
    return root;
}

template <typename T>
void printOrderTree(Node<T>* root)
{
    if(root) {
        /* print data assending order */
        printOrderTree<T>(root->lChild);
        std::cout << "value: " << root->value << ", height: " << root->height << std::endl;
        printOrderTree<T>(root->rChild);
    }
}