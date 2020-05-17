#ifndef NETWORK_BYTES_H
#define NETWORK_BYTES_H

#include <cstdint>

class NetWorkBytes {
public:
    static uint16_t u_ntohs(uint16_t data_short);
    static uint16_t u_htons(uint16_t data_short);
    static uint32_t u_ntohl(uint32_t data_long);
    static uint32_t u_htonl(uint32_t data_long);
    static uint64_t u_ntohll(uint64_t data_llong);
    static uint64_t u_htonll(uint64_t data_llong);
};

#endif