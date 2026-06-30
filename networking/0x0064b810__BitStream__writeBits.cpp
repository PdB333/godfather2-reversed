// FUNC_NAME: BitStream::writeBits
bool __thiscall BitStream::writeBits(uint numBits, const byte* srcData)
{
    // +0x0c: pointer to byte buffer (uint8*)
    // +0x18: current write position (in bits)
    // +0x30: capacity (in bytes)
    // +0x34: bit count? (not used here)

    if (srcData == nullptr)
        return true;

    uint currentBitPos = *(uint*)(this + 0x18);
    uint capacityBytes = *(uint*)(this + 0x30);
    // Check if we need to expand buffer
    if (capacityBytes < (uint)(*(int*)(this + 0x18) + (int)numBits)) {
        if (!expandBuffer(this))  // call FUN_0064b7c0
            return false;
    }

    uint bitOffset = currentBitPos & 7;
    uint byteOffset = currentBitPos >> 3;
    byte* buffer = *(byte**)(this + 0x0c);
    byte* dst = buffer + byteOffset;
    uint bitsInFirstByte = 8 - bitOffset;
    bool fitsInFirstByte = numBits <= bitsInFirstByte;

    if (fitsInFirstByte) {
        byte mask = (1 << numBits) - 1;
        *dst = (*srcData & mask) << bitOffset | ~(mask << bitOffset) & *dst;
        *(uint*)(this + 0x18) = currentBitPos + numBits;
        return true;
    }

    uint totalNewBitPos = currentBitPos + numBits;
    if (bitOffset == 0) {
        // Byte-aligned case
        *(uint*)(this + 0x18) = totalNewBitPos;
        if (numBits > 7) {
            uint fullBytes = numBits >> 3;
            do {
                *dst = *srcData;
                dst++;
                srcData++;
                numBits -= 8;
                fullBytes--;
            } while (fullBytes != 0);
        }
        if (numBits != 0) {
            byte mask = (1 << numBits) - 1;
            *dst = ~mask & *dst | *srcData & mask;
            return true;
        }
    }
    else {
        // Misaligned case
        byte partialMask = (0xFF >> (bitsInFirstByte & 0x1f)) & *dst;  // keep low bits of first byte
        byte lastByteShift = (byte)bitOffset;
        byte highByteShift = (byte)bitsInFirstByte;
        *(uint*)(this + 0x18) = totalNewBitPos;

        if (numBits > 7) {
            uint fullBytes = numBits >> 3;
            do {
                byte srcByte = *srcData;
                srcData++;
                *dst = (srcByte << bitOffset) | partialMask;
                dst++;
                partialMask = srcByte >> (highByteShift & 0x1f);
                numBits -= 8;
                fullBytes--;
            } while (fullBytes != 0);
        }

        byte finalMask = (0xFF >> (7 - ((totalNewBitPos - 1) & 7) & 0x1f));
        if (numBits == 0) {
            *dst = ~finalMask & *dst | finalMask & partialMask;
            return true;
        }
        if (numBits <= bitsInFirstByte) {
            *dst = ((*srcData << bitOffset) | partialMask) & finalMask | ~finalMask & *dst;
            return true;
        }
        byte srcByte = *srcData;
        *dst = (srcByte << bitOffset) | partialMask;
        dst[1] = (srcByte >> (highByteShift & 0x1f)) & finalMask | ~finalMask & dst[1];
    }
    return true;
}