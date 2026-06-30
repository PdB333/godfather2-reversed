// FUN_NAME: BitStream::finalizePacket
// Address: 0x0064c980
// Role: Aligns bitstream to byte boundary, computes 32-byte hash (using 0x28 parameter), and copies result to output buffer.

void BitStream::finalizePacket(int offset, void* outputBuffer) // __thiscall
{
    // Align bit count to byte boundary (round up bits to bytes)
    uint alignedByteCount = (mBitCount + 7) >> 3;          // +0x18
    mBitCount = alignedByteCount * 8;                      // +0x18

    // Temporary bitstream writer context (212 bytes)
    char bitContext[212];                                   // local_d4
    BitStream::initContext(bitContext);                     // 0x006595c0

    // Write the current buffer bytes into the context
    BitStream::appendBytes(bitContext, mBuffer, alignedByteCount); // 0x00659640; +0xc

    // Extract a 32-byte block from the context (hash input)
    char hashInput[32];                                     // local_f4
    BitStream::copyToBuffer(bitContext, hashInput);        // 0x00659730

    // Compute hash (0x28 = 40, likely for SHA1 or similar) and store into output?
    computeHash(0x28, hashInput);                          // 0x0064b810

    // Calculate offset into original buffer and copy remaining data
    // (param_2 is the output buffer, param_1 is offset)
    int startPos = reinterpret_cast<int>(mBuffer) + offset; // +0xc
    int remainingBytes = ((mBitCount + 7) >> 3) - offset;
    memcpy(outputBuffer, startPos, startPos, remainingBytes); // 0x0065a740 (likely memcpy or similar)
}