// FUNC_NAME: TNLConnection::buildPacket
int __thiscall TNLConnection::buildPacket(int *packetDesc)
{
    int iVar1;
    int *newPacketHeader;
    int *packetDescCopy;
    int someOffset;

    packetDescCopy = packetDesc;
    someOffset = *(int *)(this + 0x1c); // +0x1c: mPacketHeaderSizeOffset? or mBaseOffset?
    if (*packetDesc != 6) {
        packetDesc = (int *)FUN_00635f60(packetDesc); // Convert packet type?
    }
    // Check if we need to flush or allocate new buffer
    if (*(int *)(this + 0x14) + 0x18 == *(int *)(this + 0x24)) { // +0x14: mWriteBufferPtr, +0x24: mBufferEnd?
        if (0x1000 < *(ushort *)(this + 0x2c)) { // +0x2c: mPacketCount?
            someOffset = FUN_00635a80(); // Flush and send?
            return someOffset;
        }
        FUN_00635c10(); // Allocate new buffer?
        if (0x1000 < *(ushort *)(this + 0x2c)) {
            FUN_00633920(); // Handle overflow?
        }
    }
    // Branch based on packet type (reliable vs unreliable)
    if (*(char *)(packetDesc[1] + 6) != '\0') { // Reliable packet
        if (*(int *)(this + 0x18) - *(int *)(this + 8) < 0xa1) { // +0x18: mBufferEnd, +0x8: mWritePos
            FUN_00635c70(); // Expand buffer?
        }
        *(int *)(this + 0x14) = *(int *)(this + 0x14) + 0x18; // Advance write pointer by header size
        newPacketHeader = *(int **)(this + 0x14);
        *newPacketHeader = (int)packetDescCopy + *(int *)(this + 0x1c) + (8 - someOffset);
        *(int *)(this + 0xc) = **(int **)(this + 0x14); // +0xc: mLastPacketSeq?
        newPacketHeader[1] = *(int *)(this + 8) + 0xa0; // Payload size? 0xa0 = 160
        newPacketHeader[2] = 1; // Flags?
        if ((*(byte *)(this + 0x30) & 1) != 0) { // +0x30: mFlags
            FUN_00635d00(0xffffffff); // Notify?
        }
        someOffset = (**(code **)(*(int *)(*(int *)(this + 0xc) + -4) + 0xc))(); // Virtual call on packet object
        return *(int *)(this + 8) + someOffset * -8;
    }
    // Unreliable packet
    iVar1 = *(int *)(packetDesc[1] + 0xc); // Descriptor pointer
    if (*(char *)(iVar1 + 0x46) != '\0') {
        FUN_00635dc0(*(undefined1 *)(iVar1 + 0x45), packetDesc + 2); // Copy data?
    }
    if (*(int *)(this + 0x18) - *(int *)(this + 8) <= (int)((uint)*(byte *)(iVar1 + 0x47) * 8)) {
        FUN_00635c70(); // Expand buffer?
    }
    *(int *)(this + 0x14) = *(int *)(this + 0x14) + 0x18;
    newPacketHeader = *(int **)(this + 0x14);
    *newPacketHeader = (int)packetDescCopy + *(int *)(this + 0x1c) + (8 - someOffset);
    someOffset = **(int **)(this + 0x14);
    *(int *)(this + 0xc) = someOffset;
    newPacketHeader[1] = someOffset + (uint)*(byte *)(iVar1 + 0x47) * 8; // Payload size based on chunk count
    newPacketHeader[3] = *(int *)(iVar1 + 0xc); // Some data pointer
    newPacketHeader[5] = 0;
    newPacketHeader[2] = 8; // Flags?
    // Zero out the payload area
    if (*(uint *)(this + 8) < (uint)newPacketHeader[1]) {
        do {
            **(int **)(this + 8) = 0;
            *(int *)(this + 8) = *(int *)(this + 8) + 8;
        } while (*(uint *)(this + 8) < (uint)newPacketHeader[1]);
    }
    *(int *)(this + 8) = newPacketHeader[1];
    return 0;
}