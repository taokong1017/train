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
    void addNode(const T& data){ mRoot = insertNode(mRoot, data);}
    bool findTarget(const T& target) { return searchNode(mRoot, target);}
    void printOrderTree() { 
        if(!mRoot) return;
        printOrderTree(mRoot, 0);
    }
    void removeData(const T& target) { mRoot = removeNode(mRoot, target);}

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
        //std::cout << "rightRightRotate" << std::endl;
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
        //std::cout << "leftLeftRotate" << std::endl;
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
        //std::cout << "leftRightRotate" << std::endl;
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
        //std::cout << "rightLeftRotate" << std::endl;
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
        root->height = std::max<int>(height(root->lChild), height(root->rChild)) + 1;

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
    void printOrderTree(Node<T>* root, int layer)
    {
        if(root) {
            /* print data assending order */
            printOrderTree(root->rChild, layer+1);
            for(int i=0; i< layer; i++) {
                std::cout << "    ";
            }
            std::cout << root->value << std::endl;
            printOrderTree(root->lChild, layer+1);
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
            return searchNode(root->lChild, data);
        } else {
            return searchNode(root->rChild, data);
        }
    } 
    Node<T>* removeNode(Node<T>* root, const T& data)
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
        root->height = std::max<int>(height(root->lChild), height(root->rChild)) + 1;

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
    inline size_t height(Node<T>* node) { return !node ? -1 : node->height;}

private:
    Node<T>* mRoot;
};


#endif
