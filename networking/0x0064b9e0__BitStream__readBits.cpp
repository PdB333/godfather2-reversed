// FUNC_NAME: BitStream::readBits
// 0x0064b9e0
// Reads a specified number of bits from a bitstream buffer.
// Returns 1 on success, 0 if not enough bits remain.
// Buffer pointer at this+0x0C, current bit offset at this+0x18, total bits at this+0x2C, overflow flag at this+0x1C.

int __thiscall BitStream::readBits(uint numBits, byte *outData)
{
    uint currentBitOffset;
    uint alignedBits;
    byte *srcPtr;
    uint numBytes;
    byte partialByte;
    byte shiftLeft;
    byte *dstPtr;
    byte b;

    if (numBits == 0)
        return 1;

    currentBitOffset = *(uint *)(this + 0x18);
    if (*(uint *)(this + 0x2C) < currentBitOffset + numBits) {
        *(undefined1 *)(this + 0x1C) = 1; // overflow flag
        return 0;
    }

    alignedBits = currentBitOffset & 7;
    srcPtr = (byte *)((currentBitOffset >> 3) + *(int *)(this + 0xC));
    numBytes = (numBits + 7) >> 3;

    if (alignedBits == 0) {
        // Byte-aligned: copy full bytes
        for (; numBytes != 0; numBytes--)
        {
            *outData = *srcPtr;
            outData++;
            srcPtr++;
        }
        *(int *)(this + 0x18) = *(int *)(this + 0x18) + numBits;
        return 1;
    }

    // Misaligned: need to handle partial bytes
    partialByte = *srcPtr >> alignedBits;
    *(uint *)(this + 0x18) = currentBitOffset + numBits;
    shiftLeft = (byte)(8 - alignedBits);
    dstPtr = outData;

    if (7 < numBits) {
        byte *srcIter = srcPtr;
        byte *dstIter = outData;
        byte running = partialByte;
        uint remaining = numBits;

        do {
            srcIter++;
            b = *srcIter >> alignedBits;
            *dstIter = (*srcIter << (shiftLeft & 0x1f)) | running;
            dstIter++;
            remaining -= 8;
            numBytes--;
            running = b;
        } while (numBytes != 0);
        partialByte = running;
        dstPtr = dstIter;
    }

    if (numBits != 0) {
        if (numBits <= 8 - alignedBits) {
            *dstPtr = partialByte;
            return 1;
        }
        *dstPtr = (srcPtr[1] << (shiftLeft & 0x1f)) | partialByte;
    }
    return 1;
}