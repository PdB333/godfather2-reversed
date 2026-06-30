// FUNC_NAME: TNLBitStream::ensureWriteCapacity
// Function at 0x0064b7c0 - ensures the bitstream buffer is large enough to accommodate numBits additional bits
// with a fixed MTU overhead of 0x5DC (1500) bytes, typical for Ethernet packet framing.

uint TNLBitStream::ensureWriteCapacity(int numBits) {
    // Compute required byte size:
    //   current write position in bytes (mBitWriteHead >> 3) + rounded-up bytes for new bits + MTU overhead
    uint requiredBytes = (numBits + 7 + (mBitWriteHead >> 3)) + 0x5DC;

    if (mAllocatedBytes < requiredBytes) {
        // Buffer too small; attempt to grow if owned
        if (mOwnsBuffer) {
            mAllocatedBytes = requiredBytes;
            mBuffer = _realloc(mBuffer, requiredBytes);
            int newBitCapacity = requiredBytes * 8;
            mBitCapacity = newBitCapacity;
            mBitWriteHead = newBitCapacity; // Note: original code also sets +0x2C; treat as capacity, +0x30 as current head
            // Return success indicator (CONCAT31( (int3)(newBitCapacity>>8), 1) )
            return 1;
        }
    }
    else {
        // Size is sufficient; just update allocated size
        mAllocatedBytes = requiredBytes;
    }

    // Set overflow/valid flag and return error or capacity
    mOverflowBit = 1; // +0x1C = 1
    return mBitWriteHead & 0xFFFFFF00; // Return masked bit position (or status)
}