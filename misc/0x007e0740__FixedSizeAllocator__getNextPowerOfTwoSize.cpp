// FUNC_NAME: FixedSizeAllocator::getNextPowerOfTwoSize
// Address: 0x007e0740
// Returns the next power-of-two size >= requested size that is free in the allocation bitmap (bitmap at this+0x04).
// Maximum supported size is 0x40000000 (2^30). Returns 0 if no suitable size found.

uint __thiscall FixedSizeAllocator::getNextPowerOfTwoSize(uint requestedSize) {
    uint currentSize;
    uint result;

    // Exact match with maximum size
    if (requestedSize == 0x40000000) {
        return 0x40000000;
    }

    result = 0;
    currentSize = requestedSize * 2;

    // Search for the next power-of-two >= requestedSize that is marked free in the bitmap
    while (currentSize <= 0x40000000) {
        result = currentSize;
        // Check if the allocated bit for this size is free (bit set means free)
        if ((result != 0) && ((*(uint *)(this + 4) & result) == result)) {
            // Found free slot
            break;
        }
        currentSize = result * 2;
    }

    // If loop exited due to exceeding max size, return 0
    if (currentSize > 0x40000000) {
        result = 0;
    }

    return result;
}