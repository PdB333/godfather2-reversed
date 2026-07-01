// FUNC_NAME: BitStream::readPackedFlag
// Address: 0x008daf70
// The function reads a packed boolean/follow-bit pattern from a bitstream.
// It checks for overflow, processes two consecutive bits, and may call helpers 
// if the first bit indicates additional data.

void BitStream::readPackedFlag() {
    // +0x0c: pointer to bit buffer (bytes)
    // +0x18: current bit position
    // +0x1c: overflow flag (1 = overflow occurred)
    // +0x2c: total number of bits in stream

    ensureReadableBits(this); // 0x00472c10: validates buffer bounds, possibly expands

    uint currentBit = *(uint*)(this + 0x18);

    // Check if we've already exceeded total bits
    if (*(uint*)(this + 0x2c) < currentBit) {
        *(byte*)(this + 0x1c) = 1; // set overflow flag
        return;
    }

    // Read first bit (bit at position currentBit)
    byte byteWithBit = *(byte*)((currentBit >> 3) + *(int*)(this + 0xc));
    if ((byteWithBit & (1 << (currentBit & 7))) != 0) {
        // First bit set: handle error and read additional data
        signalOverflowError(0); // 0x004a8ec0 - likely sets error code
        readMoreDataToBuffer(this, (byte*)&local_8); // 0x004a9360 - reads extra bits into temp buffer
    }
    // Advance past the first bit
    *(uint*)(this + 0x18) = currentBit + 1;

    // Now read second bit (at the new position)
    uint newCurrent = *(uint*)(this + 0x18);
    if (newCurrent <= *(uint*)(this + 0x2c)) {
        byte secondByte = *(byte*)((newCurrent >> 3) + *(int*)(this + 0xc));
        int beforeIncrement = *(int*)(this + 0x18);
        uint tempInc = beforeIncrement + 1;
        *(uint*)(this + 0x18) = tempInc; // increment by one (read second bit)
        if ((secondByte & (1 << (newCurrent & 7))) != 0) {
            // Second bit set: check for overflow before skipping an extra position
            if (*(uint*)(this + 0x2c) < tempInc) {
                goto overflowLabel;
            }
            // Skip one more bit (i.e., effectively advance two from beforeIncrement)
            *(int*)(this + 0x18) = beforeIncrement + 2;
        }
        return;
    }

overflowLabel:
    *(byte*)(this + 0x1c) = 1; // set overflow flag
    return;
}