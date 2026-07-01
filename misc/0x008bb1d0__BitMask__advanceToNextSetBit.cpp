// FUNC_NAME: BitMask::advanceToNextSetBit
// Address: 0x008bb1d0
// Role: Advances the current index to the next set bit in an internal bitmask; if a set bit is found, triggers a callback with a given parameter.

void __thiscall BitMask::advanceToNextSetBit(BitMask *this) {
    uint currentIndex;
    byte bitByte;
    int totalBits;
    byte *bitmapData;

    // Call base/helper function (likely updates internal state or resets if needed)
    FUN_00472c10(this);

    currentIndex = this->currentIndex; // +0x18
    totalBits = this->totalBits; // +0x2c

    // If we've reached or passed the total number of bits, mark as done and return
    if (totalBits < currentIndex) {
        this->doneFlag = 1; // +0x1c
        return;
    }

    // Compute the byte in the bitmap where the current bit resides
    bitmapData = this->bitmapData; // +0x0c
    bitByte = bitmapData[currentIndex >> 3]; // index/8

    // Advance the current index
    this->currentIndex = currentIndex + 1;

    // Check if the current bit is set (using (index & 7) as the bit position)
    if ((bitByte & (1 << (currentIndex & 7))) != 0) {
        // If set, call a debug/log/assert function with severity 0x20 and this pointer
        FUN_0064b9e0(0x20, &this);
    }
    return;
}