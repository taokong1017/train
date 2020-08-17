#include <iostream>
#include "test.h"



int main(int argc, char **argv)
{
    Train::Test test;
    test.setData(10);
    std::cout << test.getData() << std::endl;

    return 0;
}
