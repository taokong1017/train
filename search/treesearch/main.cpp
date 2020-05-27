#include <iostream>
#include "avltree.h"

int main(int argc, char**argv)
{
    std::vector<int> data {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 11, 12, 13, 14};
    std::cout << "origin tree: " << std::endl;
    AvlTree<int> tree(data);
    tree.printOrderTree();

    int delData = 8;
    std::cout << "delete data: " << delData << std::endl;
    tree.removeData(delData);

    std::cout << "\nremove tree: " << std::endl;
    tree.printOrderTree();
    return 0;
}