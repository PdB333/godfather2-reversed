// FUNC_NAME: getAlignedAllocSize
int getAlignedAllocSize(uint size, uint alignment, int count)
{
    uint remainder;

    // Minimum alignment is 4 bytes
    if (alignment < 4) {
        alignment = 4;
    }

    // Compute the offset from the previous aligned boundary
    remainder = (alignment - 1) & size;

    // If not already aligned, round up to the next multiple
    if (remainder != 0) {
        size = (alignment - remainder) + size;
    }

    // Return total size = aligned element size * element count
    return size * count;
}