#include <algorithm>
#include "avltree.h"

template <typename T>
AvlTree<T>::AvlTree(const std::vector<T>& list)
{

}

template <typename T>
void AvlTree<T>::addNode(const T& data)
{

}

template <typename T>
void AvlTree<T>::printTree()
{

}

template <typename T>
Node<T>* AvlTree<T>::newNode(const T& data, size_t height, Node<T>* lchild, Node<T>* rchild)
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
 *                root                newRoot
 *               /    \              /       \
 *           newRoot   c    ==>     a        root
 *          /       \                       /     \
 *        a          b                     b       c    
  */
template <typename T>
Node<T>* AvlTree<T>::RightRightRotate(Node<T>* root)
{
    Node<T>* newRoot = root->lChild;
    root->lChild = newRoot->rChlid;
    newRoot->rChlid = root;
    root->height = std::max<int>(height(root->lChild), height(root->rChlid)) + 1;
    newRoot->height = std::max<int>(height(newRoot->lChild), height(newRoot->rChlid)) + 1;
    return newRoot;
}


template <typename T>
Node<T>* AvlTree<T>::LeftLeftRotate(Node<T>* root)
{

}
