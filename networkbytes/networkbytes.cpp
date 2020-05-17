#include "networkbytes.h"

static union
{
    uint8_t  uchar_order[2];
    uint16_t uint16_order;
} host_order = { { 'L', 'B' } };

#define IS_LITTLE_ENDIAN ('L' == host_order.uchar_order[0])
#define IS_BIG_ENDIAN    ('B' == host_order.uchar_order[0])

uint16_t NetWorkBytes::u_ntohs(uint16_t data_short)
{
    if (IS_LITTLE_ENDIAN)
        return ((data_short << 8) | (data_short >> 8));
    return data_short;
}

uint16_t NetWorkBytes::u_htons(uint16_t data_short)
{
    if (IS_LITTLE_ENDIAN)
        return ((data_short << 8) | (data_short >> 8));
    return data_short;
}

uint32_t NetWorkBytes::u_ntohl(uint32_t data_long)
{
    if (IS_LITTLE_ENDIAN)
        return (((data_long             ) << 24) |
                ((data_long & 0x0000FF00) <<  8) |
                ((data_long & 0x00FF0000) >>  8) |
                ((data_long             ) >> 24));
    return data_long;
}

uint32_t NetWorkBytes::u_htonl(uint32_t data_long)
{
    if (IS_LITTLE_ENDIAN)
        return (((data_long             ) << 24) |
                ((data_long & 0x0000FF00) <<  8) |
                ((data_long & 0x00FF0000) >>  8) |
                ((data_long             ) >> 24));
    return data_long;
}

uint64_t NetWorkBytes::u_ntohll(uint64_t data_llong)
{
    if (IS_LITTLE_ENDIAN)
        return (((data_llong                     ) << 56) |
                ((data_llong & 0x000000000000FF00) << 40) |
                ((data_llong & 0x0000000000FF0000) << 24) |
                ((data_llong & 0x00000000FF000000) <<  8) |
                ((data_llong & 0x000000FF00000000) >>  8) |
                ((data_llong & 0x0000FF0000000000) >> 24) |
                ((data_llong & 0x00FF000000000000) >> 40) |
                ((data_llong                     ) >> 56));
    return data_llong;
}

uint64_t NetWorkBytes::u_htonll(uint64_t data_llong)
{
    if (IS_LITTLE_ENDIAN)
        return (((data_llong                     ) << 56) |
                ((data_llong & 0x000000000000FF00) << 40) |
                ((data_llong & 0x0000000000FF0000) << 24) |
                ((data_llong & 0x00000000FF000000) <<  8) |
                ((data_llong & 0x000000FF00000000) >>  8) |
                ((data_llong & 0x0000FF0000000000) >> 24) |
                ((data_llong & 0x00FF000000000000) >> 40) |
                ((data_llong                     ) >> 56));
    return data_llong;
}