// FUNC_NAME: PacketLayout::computeOffsets
void __thiscall PacketLayout::computeOffsets(uint baseOffset) {
    int count;

    // Align baseOffset to 16-byte boundary if not already aligned
    if ((baseOffset & 0xf) != 0) {
        baseOffset = (baseOffset & 0xfffffff0) + 0x10;
    }

    // Clear all offset fields first (they will be set if corresponding count/size is non-zero)
    this->mReliableBitOffset = 0;  // +0x6c
    this->mAckBitOffset = 0;       // +0x74
    this->mGhostBitOffset = 0;     // +0x70
    this->mDataOffset1 = 0;        // +0x50
    this->mDataOffset2 = 0;        // +0x4c
    this->mDataOffset3 = 0;        // +0x54
    this->mShortOffset1 = 0;       // +0x5c
    this->mShortOffset2 = 0;       // +0x60
    this->mDataOffset4 = 0;        // +0x58
    this->mShortOffset3 = 0;       // +0x64 (100 decimal)
    this->mShortOffset4 = 0;       // +0x68
    this->mLastOffset1 = 0;        // +0x7c
    this->mLastOffset2 = 0;        // +0x78
    this->mFinalOffset = 0;        // +0x44

    // Bit array section 1: 8-byte header + (count/32) * 8 bytes for bits
    if (this->mReliableCount != 0) {           // +0x2a (short)
        count = this->mReliableCount - 1;
        this->mReliableBitOffset = baseOffset;
        // Round up count to nearest multiple of 32, then *8 (8 bytes per 32-bit group)
        baseOffset += 8 + ((count + (count >> 31 & 0x1f)) >> 5) * 8;
    }

    // Bit array section 2 (acknowledgements)
    if (this->mAckCount != 0) {                // +0x32 (short)
        count = this->mAckCount - 1;
        this->mAckBitOffset = baseOffset;
        baseOffset += 8 + ((count + (count >> 31 & 0x1f)) >> 5) * 8;
    }

    // Bit array section 3 (ghost updates)
    if (this->mGhostCount != 0) {              // +0x34 (short)
        count = this->mGhostCount - 1;
        this->mGhostBitOffset = baseOffset;
        baseOffset += 8 + ((count + (count >> 31 & 0x1f)) >> 5) * 8;
    }

    // Advance by fixed extra size (e.g., padding or header extension)
    baseOffset += this->mExtraSize;            // +0x3a (short)

    // Data sections with sizes stored as ints
    if (this->mDataSize1 != 0) {               // +0x4 (int)
        this->mDataOffset1 = baseOffset;
        baseOffset += this->mDataSize1;
    }

    if (this->mDataSize2 != 0) {               // +0x14 (int)
        this->mDataOffset2 = baseOffset;
        baseOffset += this->mDataSize2;
    }

    if (this->mDataSize3 != 0) {               // +0x8 (int)
        this->mDataOffset3 = baseOffset;
        baseOffset += this->mDataSize3;
    }

    // Short-sized sections
    if (this->mShortSize1 != 0) {              // +0x20 (ushort)
        this->mShortOffset1 = baseOffset;
        baseOffset += this->mShortSize1;
    }

    if (this->mShortSize2 != 0) {              // +0x22 (ushort)
        this->mShortOffset2 = baseOffset;
        baseOffset += this->mShortSize2;
    }

    if (this->mDataSize4 != 0) {               // +0xc (int)
        this->mDataOffset4 = baseOffset;
        baseOffset += this->mDataSize4;
    }

    if (this->mShortSize3 != 0) {              // +0x1c (ushort)
        this->mShortOffset3 = baseOffset;
        baseOffset += this->mShortSize3;
    }

    if (this->mShortSize4 != 0) {              // +0x1e (ushort)
        this->mShortOffset4 = baseOffset;
        baseOffset += this->mShortSize4;
    }

    // Final section conditional on a count field
    if (this->mLastCount != 0) {               // +0x26 (ushort)
        this->mLastOffset1 = baseOffset;
        this->mLastOffset2 = baseOffset + this->mLastCount;  // +0x78
        // Compute final offset: baseOffset + lastCount + (shortSize * 4), but only if condition flag is set
        this->mFinalOffset = (this->mConditionFlag != 0) ?      // +0x2e (short)
                            (this->mLastOffset2 + (uint)this->mPerElementSize * 4) : 0; // +0x28 (ushort)
        return;
    }

    // If last count is zero, store zero in last offsets and set finalOffset based on condition
    this->mLastOffset1 = 0;
    this->mLastOffset2 = 0;
    this->mFinalOffset = (this->mConditionFlag != 0) ? baseOffset : 0;
}