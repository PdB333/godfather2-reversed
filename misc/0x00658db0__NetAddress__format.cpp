// FUNC_NAME: NetAddress::format
#include <cstdint>

// Static buffer for string formatting
static char g_formatBuffer[256];

// Format this network address as a string.
// The address type determines the format:
//   - type == 0: IP address (IPv4)
//   - type != 0: IPX address
// The returned pointer is to a static buffer; subsequent calls overwrite it.
char* NetAddress::format() const
{
    // If type is non‑zero, the address is IPX.
    if (type != 0)
    {
        // IPX address fields (all in host byte order)
        uint32_t network  = ipx.network;  // +0x04: 4 bytes
        uint32_t nodeHigh = ipx.nodeHigh; // +0x08: first 4 bytes of node
        uint16_t nodeLow  = ipx.nodeLow;  // +0x0C: last 2 bytes of node

        // Format: IPX:NNNNNNNN:NNNNNNNNNN:PP (network, 6‑byte node, port)
        formatString(g_formatBuffer, sizeof(g_formatBuffer),
            "IPX:%.2X%.2X%.2X%.2X:%.2X%.2X%.2X%.2X%.2X%.2X:%d",
            (network >> 24) & 0xFF,
            (network >> 16) & 0xFF,
            (network >> 8)  & 0xFF,
             network        & 0xFF,
            (nodeHigh >> 24) & 0xFF,
            (nodeHigh >> 16) & 0xFF,
            (nodeHigh >> 8)  & 0xFF,
             nodeHigh        & 0xFF,
            (nodeLow  >> 8)  & 0xFF,
             nodeLow         & 0xFF,
             port);                      // +0x02: port in host order

        return g_formatBuffer;
    }

    // IPv4 address (stored in host byte order at offset +0x04)
    uint32_t ip   = addr.ip;
    uint16_t port = this->port; // host order

    // Check for special addresses (broadcast and any)
    if (ip == 0xFFFFFFFF)
    {
        // Broadcast address
        formatString(g_formatBuffer, sizeof(g_formatBuffer), "IP:Broadcast:%d", port);
    }
    else if (ip == 0x00000000)
    {
        // Any address
        formatString(g_formatBuffer, sizeof(g_formatBuffer), "IP:Any:%d", port);
    }
    else
    {
        // Normal address
        formatString(g_formatBuffer, sizeof(g_formatBuffer), "IP:%d.%d.%d.%d:%d",
            (ip >> 24) & 0xFF,
            (ip >> 16) & 0xFF,
            (ip >> 8)  & 0xFF,
             ip        & 0xFF,
             port);
    }

    return g_formatBuffer;
}