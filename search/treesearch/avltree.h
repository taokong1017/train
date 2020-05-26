#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <vector>

template<typename T>
struct TreeNode 
{
    T value;
    int height;
    TreeNode<T>* lChild;
    TreeNode<T>* rChlid;
};

template<typename T>
using Node = struct TreeNode<T>;

template<typename T>
class AvlTree
{
public:
    AvlTree();
    AvlTree(const std::vector<T>& list);
    virtual ~AvlTree(){}
    void addNode(const T& data);
    bool searchData(const T& target);
    void printOrderTree();

protected:
    Node<T>* rightRightRotate(Node<T>* k1);
    Node<T>* leftLeftRotate(Node<T>* k1);
    Node<T>* leftRightRotate(Node<T>* k1);
    Node<T>* rightLeftRotate(Node<T>* k1);
    Node<T>* insertNode(Node<T>* root, const T& data);
    void printOrderTree(Node<T>* root);

private:
    Node<T>* newNode(const T& data,  Node<T>* lchild = nullptr, Node<T>* rchild = nullptr, size_t height = 0);
    inline size_t height(Node<T>* node) { return node == nullptr ? -1 : node->height;}

private:
    Node<T>* mRoot;
};


#endif
