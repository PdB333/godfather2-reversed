// FUNC_NAME: NetAddressToString

#include <winsock2.h>
#include <stdio.h>

struct NetAddress {
    unsigned short type;      // 0 = IP, 1 = IPX (or other)
    unsigned short port;      // host byte order
    union {
        struct {
            unsigned char network[4];
            unsigned char node[6];
        } ipx;
        struct {
            unsigned char bytes[4];
        } ip;
    } addr;
};

char* NetAddressToString(NetAddress* addr) {
    static char buffer[256];

    if (addr->type != 0) {
        // IPX address
        uint32_t network = *(uint32_t*)((char*)addr + 4);   // bytes 4-7 (network)
        uint32_t nodeHigh = *(uint32_t*)((char*)addr + 8);  // bytes 8-11 (first 4 node bytes)
        uint32_t nodeLow  = *(uint32_t*)((char*)addr + 12); // bytes 12-15 (only low 2 used for last 2 node bytes)
        snprintf(buffer, sizeof(buffer),
            "IPX:%.2X%.2X%.2X%.2X:%.2X%.2X%.2X%.2X%.2X%.2X:%d",
            (network >> 24) & 0xFF,
            (network >> 16) & 0xFF,
            (network >> 8) & 0xFF,
            network & 0xFF,
            (nodeHigh >> 24) & 0xFF,
            (nodeHigh >> 16) & 0xFF,
            (nodeHigh >> 8) & 0xFF,
            nodeHigh & 0xFF,
            (nodeLow >> 8) & 0xFF,
            nodeLow & 0xFF,
            addr->port);
        return buffer;
    }

    // IP address
    uint32_t ip = *(uint32_t*)((char*)addr + 4);  // host byte order
    uint32_t ipNet = htonl(ip);                   // network byte order for comparisons

    if (ipNet == 0xFFFFFFFF) {
        snprintf(buffer, sizeof(buffer), "IP:Broadcast:%d", addr->port);
    } else if (ipNet == 0) {
        snprintf(buffer, sizeof(buffer), "IP:Any:%d", addr->port);
    } else {
        snprintf(buffer, sizeof(buffer),
            "IP:%d.%d.%d.%d:%d",
            (ip >> 24) & 0xFF,
            (ip >> 16) & 0xFF,
            (ip >> 8) & 0xFF,
            ip & 0xFF,
            addr->port);
    }
    return buffer;
}