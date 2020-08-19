#include <iostream>
#include "traits.h"

int main(int argc, char **argv)
{
    int a, b;
    std::cout << std::boolalpha;
    std::cout << "a and b is same type: " << Train::Traits::is_same<decltype(a), decltype(b)>::value << std::endl;

    double c;
    std::cout << "a and c is same type: " << Train::Traits::is_same<decltype(a), decltype(c)>::value << std::endl;

    return 0;
}