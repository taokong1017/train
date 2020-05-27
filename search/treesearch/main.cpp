#include <iostream>
#include "avltree.h"

int main(int argc, char**argv)
{
    std::vector<int> data {1,3,5,2,0};
    AvlTree<int> tree(data);
    return 0;
}