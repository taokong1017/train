#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <vector>

template<typename T>
struct TreeNode 
{
    T value;
    size_t height;
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
    Node<T>* RightR

private:
    Node<T>* newNode(const T& data);

private:
    Node<T>* root;
};


#endif
