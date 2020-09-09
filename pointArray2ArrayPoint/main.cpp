#include <iostream>
#include "string"

int main(int argc, char **argv)
{
    char* args1[2] = {NULL};
    char* args2[2] = {NULL};
    char* args3[2] = {NULL};
    char data1[2][100] = {"hellow1", "world1"};
    char data2[2][100] = {"hellow2", "world2"};
    char data3[2][100] = {"hellow3", "world3"};

    args1[0] = data1[0];
    args1[1] = data1[1];
    std::cout << "args1-0: " << args1[0] << std::endl;
    std::cout << "args1-1: " << args1[1] << std::endl;

    char** args = args1;
    std::cout << "args1-2: " << *args << std::endl;
    std::cout << "args1-3: " << *(args+1) << std::endl;

    args2 = reinterpret_cast<char**>(data2);
    std::cout << "args2-0: " << args2[0] << std::endl;
    std::cout << "args2-1: " << args2[1] << std::endl;

    args3 = (char**)data3;
    std::cout << "args3-0: " << args3[0] << std::endl;
    std::cout << "args3-1: " << args3[1] << std::endl;

    return 0;
}