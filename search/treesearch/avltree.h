#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <vector>
#include <iostream>
#include <algorithm>

template<typename T>
struct TreeNode 
{
    T value;
    int height;
    TreeNode<T>* lChild;
    TreeNode<T>* rChild;
};

template<typename T>
using Node = struct TreeNode<T>;

template<typename T>
class AvlTree
{
public:
    AvlTree():mRoot(nullptr) {}
    AvlTree(const std::vector<T>& list)
    : mRoot(nullptr)
    {
        for(const auto& data : list) {
            addNode(data);
        }
    }
    virtual ~AvlTree(){}
    void addNode(const T& data){mRoot = insertNode(mRoot, data);}
    bool findTarget(const T& target) { return searchNode(mRoot, target);}
    void printOrderTree() { printOrderTree(mRoot);}
    void removeData(const T& target) { removeNode(mRoot, target);}

protected:
    /*
    *            k1                    k2
    *          /    \                /    \
    *        k2       c    ==>      a      k1
    *       /   \                        /    \
    *      a     b                      b      c    
    */
    Node<T>* rightRightRotate(Node<T>* k1)
    {
        Node<T>* k2 = k1->lChild;
        k1->lChild = k2->rChild;
        k2->rChild = k1;
        k1->height = std::max<int>(height(k1->lChild), height(k1->rChild)) + 1;
        k2->height = std::max<int>(height(k2->lChild), height(k2->rChild)) + 1;
        return k2;
    }

    /*
    *         k1                         k2
    *       /    \                     /    \
    *      a      k2     ==>         k1      c
    *           /    \             /    \
    *          b      c          a       b  
    */
    Node<T>* leftLeftRotate(Node<T>* k1)
    {
        Node<T>* k2 = k1->rChild;
        k1->rChild = k2->lChild;
        k2->lChild = k1;
        k1->height = std::max<int>(height(k1->lChild), height(k1->rChild)) + 1;
        k2->height = std::max<int>(height(k2->lChild), height(k2->rChild)) + 1;
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
    Node<T>* leftRightRotate(Node<T>* k1)
    {
        k1->lChild = leftLeftRotate(k1->lChild);
        return rightRightRotate(k1);
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

    Node<T>* rightLeftRotate(Node<T>* k1)
    {
        k1->rChild = rightRightRotate(k1->rChild);
        return leftLeftRotate(k1);
    }

    Node<T>* insertNode(Node<T>* root, const T& data)
    {
        /* add new node*/
        if(!root) {
            return root = newNode(data);
        } else if(data < root->value) {
            root->lChild = insertNode(root->lChild, data);
        } else {
            root->rChild = insertNode(root->rChild, data);
        }

        /* adjust avl tree heigh, difference less than 2*/
        int lheight = height(root->lChild);
        int rheight = height(root->rChild);
        if (lheight - rheight >= 2) {
            if (data < root->lChild->value) {
                root = rightRightRotate(root);
            } else {
                root = leftRightRotate(root);
            }
        }
        if(rheight - lheight >= 2) {
            if (data < root->rChild->value) {
                root = rightLeftRotate(root);
            } else {
                root = leftLeftRotate(root);
            }
        }
        return root;
    }
    void printOrderTree(Node<T>* root)
    {
        if(root) {
            /* print data assending order */
            printOrderTree(root->lChild);
            std::cout << "value: " << root->value << ", height: " << root->height << std::endl;
            printOrderTree(root->rChild);
        }
    }
    bool searchNode(Node<T>* root, const T& data)
    {
        if (!root) {
            return false;
        }

        if(data == root->value ) {
            return true;
        } else if (data < root->value ) {
            return searchNode(root->lChlid);
        } else {
            return searchNode(root->rChild);
        }
    } 
    bool removeNode(Node<T>* root, const T& data)
    {
        if(!root) {
            return nullptr;
        }

        if (root->value == data) {
            if(!root->rChild) {
                Node<T>* node = root->lChild;
                delete root;
                return node;
            } else {
                Node<T>* node = root->rChild;
                while(node->lChild) {
                    node = node->lChild;
                }
                root->value = node->value;
                root->rChild = removeNode(root->rChild, node->value);
            }
        } else if(data < root->value) {
            root->lChild = removeNode(root->lChild, data);
        } else {
            root->rChild = removeNode(root->rChild, data);
        }
        /* adjust avl tree heigh, difference less than 2*/
        int lheight = height(root->lChild);
        int rheight = height(root->rChild);
        if (lheight - rheight >= 2) {
            if (data < root->lChild->value) {
                root = rightRightRotate(root);
            } else {
                root = leftRightRotate(root);
            }
        }
        if(rheight - lheight >= 2) {
            if (data < root->rChild->value) {
                root = rightLeftRotate(root);
            } else {
                root = leftLeftRotate(root);
            }
        }
    }

private:
    Node<T>* newNode(const T& data,  Node<T>* lchild = nullptr, Node<T>* rchild = nullptr, size_t height = 0)
    {
        Node<T>* node = new Node<T>();
        if(node) {
            node->value = data;
            node->height = height;
            node->lChild = lchild;
            node->rChild = rchild;
        }
        return node;
    }
    inline size_t height(Node<T>* node) { return node == nullptr ? -1 : node->height;}

private:
    Node<T>* mRoot;
};


#endif
