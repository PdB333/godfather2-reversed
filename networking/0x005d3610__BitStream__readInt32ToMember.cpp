// FUNC_NAME: BitStream::readInt32ToMember
__thiscall int BitStream::readInt32ToMember(void) {
    // Read 4-byte little endian integer from stream
    uint32 readPos = this->mReadOffset;          // +0x04
    uint8* buffer = this->mBuffer;               // +0x00

    uint8 byte0 = buffer[readPos];
    uint8 byte1 = buffer[readPos + 1];
    uint8 byte2 = buffer[readPos + 2];
    uint8 byte3 = buffer[readPos + 3];

    uint32 value = (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;

    this->mReadOffset = readPos + 4;

    // Store value to target object at offset 0xB4 (likely some member field)
    // Target object pointer is stored at +0x1C
    void* targetObj = *(void**)((uint8*)this + 0x1C);
    *(uint32*)((uint8*)targetObj + 0xB4) = value;

    // Return value: low 24 bits of original value shifted right by 8,
    // with bit 24 set as a success/type flag
    return ((value >> 8) & 0xFFFFFF) | (1 << 24);
}