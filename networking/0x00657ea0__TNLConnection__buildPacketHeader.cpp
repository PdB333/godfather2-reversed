// FUNC_NAME: TNLConnection::buildPacketHeader
int TNLConnection::buildPacketHeader(int socketHandle)
{
    uint32_t hostId;
    int result;

    // Retrieve the network-order value at this+0x04 (likely a connection ID or sequence number)
    hostId = ntohl(*(uint32_t *)((int)this + 4));
    
    // Process the ID through the session/connection validation function
    result = FUN_0065d130(socketHandle, &hostId);

    // Clear 8 bytes starting at this (first two words)
    *(uint64_t *)this = 0;

    // Set first two bytes to packet type constant (2 = reliable data)
    *(uint16_t *)this = htons(2);

    // Next two bytes reserved/zero (maybe channel or padding)
    *(uint16_t *)((int)this + 2) = htons(0);

    // Write back the possibly modified host ID in network byte order
    *(uint32_t *)((int)this + 4) = htonl(hostId);

    return result;
}