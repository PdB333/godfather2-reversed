// FUNC_NAME: BitStreamReader::readBit
bool BitStreamReader::readBit(bool& outBit) {
    uint32 currentBit = *(uint32*)(this + 0x18);
    uint32 totalBits = *(uint32*)(this + 0x2c);

    if (currentBit >= totalBits) {
        *(uint8*)(this + 0x1c) = 1; // set overflow flag
        outBit = false;
        return *(uint8*)(this + 0x1c) == 0; // returns false because flag is non-zero
    }

    // Calculate byte index and bit mask
    uint32 byteIndex = currentBit >> 3;
    uint8 byteVal = *(uint8*)(*(int*)(this + 0xc) + byteIndex);
    uint8 bitMask = (uint8)(1 << (currentBit & 7));
    outBit = (byteVal & bitMask) != 0;

    // Advance bit index
    *(uint32*)(this + 0x18) = currentBit + 1;

    // Return whether overflow flag is still zero (should be 0 here)
    return *(uint8*)(this + 0x1c) == 0;
}