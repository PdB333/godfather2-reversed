// FUNC_NAME: GhostConnection::computeUpdatePacketSize
int GhostConnection::computeUpdatePacketSize(int *outHeaderSize)
{
    ScopeData *scopeData = *(ScopeData **)(this + 0x04);  // +0x04: pointer to scope data
    int ghostBitCount = *(short *)(scopeData + 0x11a);    // +0x11a: number of ghost bits (short)
    int ghostByteCount = (ghostBitCount + 7) / 8;         // round up to bytes

    int packetSize = ghostByteCount * 8 + 0xb0;           // base size: 0xb0 + bits*8

    if ((*(uint *)(scopeData + 0x104) & 0x2000) != 0) {  // +0x104: flags, bit 0x2000 = hasExtendedData
        packetSize += ghostByteCount * 0x60;              // extra 96 bytes per ghost byte
    }

    char connectionType = *(char *)(scopeData + 0x154);   // +0x154: connection type byte
    if (connectionType == 1 || connectionType == 2 || connectionType == 6) {
        packetSize += ghostByteCount * 0x20;              // extra 32 bytes per ghost byte
    }

    *outHeaderSize = 0x10;                                // header size is fixed at 16 bytes
    *this &= ~2;                                          // clear bit 1 (needsUpdate flag)

    return packetSize;
}