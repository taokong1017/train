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
    AvlTree(){}
    AvlTree(const std::vector<T>& list);
    virtual ~AvlTree(){}
    void addNode(const T& data);
    bool searchData(const T& target);
    void printTree();

protected:
    Node<T>* RightRightRotate(Node<T>* root);
    Node<T>* LeftLeftRotate(Node<T>* root);

private:
    Node<T>* newNode(const T& data, size_t height, Node<T>* lchild, Node<T>* rchild);
    size_t height(Node<T>* node) { return node == nullptr ? -1 : node->height;}

private:
    Node<T>* root;
};


#endif
