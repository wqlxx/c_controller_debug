#include "cc_packet.h"

#ifdef CC_BROADCAST;
 const uint8_t eth_addr_broadcast[ETH_ADDR_LEN] UNUSED
    = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
#endif

 inline uint32_t eth_addr_is_broadcast(const uint8_t ea[6])
{
    return (ea[0] & ea[1] & ea[2] & ea[3] & ea[4] & ea[5]) == 0xff;
}
 inline uint32_t eth_addr_is_multicast(const uint8_t ea[6])
{
    return ea[0] & 1;
}
 inline uint32_t eth_addr_is_local(const uint8_t ea[6]) 
{
    return ea[0] & 2;
}
 inline uint32_t eth_addr_is_zero(const uint8_t ea[6]) 
{
    return !(ea[0] | ea[1] | ea[2] | ea[3] | ea[4] | ea[5]);
}
 inline uint32_t eth_addr_equals(const uint8_t a[ETH_ADDR_LEN],
                                   const uint8_t b[ETH_ADDR_LEN]) 
{
    return !memcmp(a, b, ETH_ADDR_LEN);
}
 inline uint64_t eth_addr_to_uint64(const uint8_t ea[ETH_ADDR_LEN])
{
    return (((uint64_t) ea[0] << 40)
            | ((uint64_t) ea[1] << 32)
            | ((uint64_t) ea[2] << 24)
            | ((uint64_t) ea[3] << 16)
            | ((uint64_t) ea[4] << 8)
            | ea[5]);
}
 inline void eth_addr_from_uint64(uint64_t x, uint8_t ea[ETH_ADDR_LEN])
{
    ea[0] = x >> 40;
    ea[1] = x >> 32;
    ea[2] = x >> 24;
    ea[3] = x >> 16;
    ea[4] = x >> 8;
    ea[5] = x;
}

/* Returns true if 'ea' is a reserved multicast address, that a bridge must
 * never forward, false otherwise. */
 inline uint32_t eth_addr_is_reserved(const uint8_t ea[ETH_ADDR_LEN])
{
    return (ea[0] == 0x01
            && ea[1] == 0x80
            && ea[2] == 0xc2
            && ea[3] == 0x00
            && ea[4] == 0x00
            && (ea[5] & 0xf0) == 0x00);
}


