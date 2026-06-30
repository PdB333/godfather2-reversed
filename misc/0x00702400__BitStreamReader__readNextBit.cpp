// FUNC_NAME: BitStreamReader::readNextBit

void BitStreamReader::readNextBit() {
    // Offset: +0x0c - pointer to bit buffer
    // Offset: +0x18 - current bit index (uint)
    // Offset: +0x1c - overflow flag (byte)
    // Offset: +0x2c - total number of bits (uint)

    // Validate or prepare the reader (FUN_007076c0)
    validateRead();

    uint currentBitIndex = *(uint*)((int)this + 0x18);
    uint totalBits = *(uint*)((int)this + 0x2c);

    if (totalBits < currentBitIndex) {
        // End of stream reached
        *(byte*)((int)this + 0x1c) = 1;
        return;
    }

    // Read the byte containing the current bit
    byte* buffer = *(byte**)((int)this + 0xc);
    byte byteVal = buffer[currentBitIndex >> 3];

    // Advance bit index
    *(uint*)((int)this + 0x18) = currentBitIndex + 1;

    // Test the current bit (bit index modulo 8)
    byte bitMask = 1 << (currentBitIndex & 7);
    if (byteVal & bitMask) {
        // Bit is set – trigger associated action (FUN_0064b9e0)
        handleBitSet(0x20, this);
    }
}