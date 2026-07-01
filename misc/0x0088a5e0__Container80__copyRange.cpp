// FUNC_NAME: Container80::copyRange
// Function address: 0x0088a5e0
// Role: Copies a range of 80-byte elements from the container's internal buffer to an external destination.
// This is likely an internal helper for operations like insert, erase, or splice within a custom container.
// Container structure: at this+0x04 is the end pointer (past the last element).
// Element size: 0x50 (80 bytes), copied as 20 dwords (0x14) per element.
// The copy moves elements from [srcStart, containerEnd) to dest, and then advances the container's end pointer
// by the number of copied elements (computed via a signed division by -5, then refined to reflect element count).

undefined4* __thiscall Container80::copyRange(Container80* this, undefined4* dest, undefined4* srcStart)
{
    undefined4* containerEnd = *(undefined4**)((char*)this + 0x04); // +0x04: end pointer
    undefined4* srcCurrent = srcStart;
    undefined4* destCurrent = dest;

    // Copy elements from [srcStart, containerEnd) to dest
    while (srcCurrent != containerEnd)
    {
        undefined4* srcNext = srcCurrent + 0x14; // Advance by 20 dwords (80 bytes)
        undefined4* destSaved = destCurrent;
        for (int i = 0x14; i != 0; --i) // Copy 20 dwords per element
        {
            *destSaved = *srcCurrent;
            srcCurrent++;
            destSaved++;
        }
        srcCurrent = srcNext;
        destCurrent = destCurrent + 0x14; // Move destination by one element
    }

    // Compute number of copied elements (signed division by -5)
    int diff = (int)srcStart - (int)dest; // Note: srcStart is source, dest is destination (backwards due to param order?)
    int elementCountDivide = (int)((long long)diff * -0x66666667LL >> 32);
    int elementCount = ((elementCountDivide >> 5) - (elementCountDivide >> 0x1f)) * 0x50; // Calculate byte offset to add
    *(int*)((char*)this + 0x04) += elementCount; // Update end pointer by this number of bytes

    return dest; // Return original destination pointer
}