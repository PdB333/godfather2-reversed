// FUNC_NAME: BitStream::writeBit
void __thiscall BitStream::writeBit(BitStream* this, bool bitValue)
{
    // Check if we need more space: current bit position + 1 exceeds capacity
    // mBitCapacity = this+0x30, mBitPosition = this+0x18
    if (this->mBitCapacity < this->mBitPosition + 1) {
        // Attempt to grow the buffer; if fails, do nothing
        if (!growBuffer()) { // FUN_0064b7c0
            return;
        }
    }

    // Compute byte offset into buffer: (bitPosition >> 3) + base buffer pointer
    // mBuffer = this+0xc
    byte* bytePtr = this->mBuffer + (this->mBitPosition >> 3);
    byte mask = 1 << (this->mBitPosition & 7);

    if (bitValue) {
        *bytePtr |= mask; // set the bit
    } else {
        *bytePtr &= ~mask; // clear the bit
    }

    // Advance bit position
    this->mBitPosition++;
}