// FUNC_NAME: PacketBitStream::readPacketHeader
void PacketBitStream::readPacketHeader(PacketHeader* outHeader)
{
    uint bitIndex;
    bool hasExtended;
    int header = outHeader;

    resetRead(this, outHeader); // FUN_008531e0: reinitialize bit read pointer

    readU16(0x10, &outHeader); // FUN_0064b9e0: read 16-bit value from bitstream (size=0x10)
    *(uint16*)(header + 6) = (uint16)outHeader; // store to outHeader->sequenceOrData

    // Read first flag bit (e.g., ackNakFlag)
    bitIndex = *(uint*)(this + 0x18); // current read bit position
    if (*(uint*)(this + 0x2c) < bitIndex) {
        *(byte*)(this + 0x1c) = 1; // overflow flag
        hasExtended = false;
    } else {
        hasExtended = (*(byte*)((bitIndex >> 3) + *(int*)(this + 0xc)) & (1 << (bitIndex & 7))) != 0;
        *(int*)(this + 0x18) = bitIndex + 1; // advance bit position
    }
    *(bool*)(header + 8) = hasExtended; // outHeader->flag1

    // Read second flag bit (e.g., extendedInfoFlag)
    bitIndex = *(uint*)(this + 0x18);
    if (*(uint*)(this + 0x2c) < bitIndex) {
        *(byte*)(this + 0x1c) = 1;
        hasExtended = false;
    } else {
        hasExtended = (*(byte*)((bitIndex >> 3) + *(int*)(this + 0xc)) & (1 << (bitIndex & 7))) != 0;
        *(int*)(this + 0x18) = bitIndex + 1;
    }
    *(bool*)(header + 9) = hasExtended; // outHeader->flag2

    if (hasExtended != false) {
        readU32(this, header + 0xc); // FUN_004a9cd0: read additional 32-bit data
        readU16(0x10, &outHeader);
        *(uint16*)(header + 6) = (uint16)outHeader; // overwrite with second 16-bit value
        return;
    }
    readU16(0x10, &outHeader);
    *(uint16*)(header + 4) = (uint16)outHeader; // store to outHeader->otherSequence
    return;
}