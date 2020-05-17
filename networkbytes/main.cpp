#include <iostream>
#include "networkbytes.h"

using namespace std;


int main(int argc, char** argv)
{
    uint16_t data1 = 0x1234;
    uint16_t data2 = NetWorkBytes::u_htons(data1);
    std::cout << hex << data1 << " " << hex << data2 << std::endl;
    uint32_t data3 = 0x12345678;
    uint32_t data4 = NetWorkBytes::u_htonl(data3);
    std::cout << hex << data3 << " " << hex << data4 << std::endl;
    uint64_t data5 = 0x1234567887654321;
    uint64_t data6 = NetWorkBytes::u_htonll(data5);
    std::cout << hex << data5 << " " << hex << data6 << std::endl;
    return 0;
}