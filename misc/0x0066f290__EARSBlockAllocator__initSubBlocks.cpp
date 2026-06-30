// FUNC_NAME: EARSBlockAllocator::initSubBlocks
void __thiscall EARSBlockAllocator::initSubBlocks(int this, int someValue, int* output, SubBlockDescriptor* descriptor) {
    // output is passed in EDI; descriptor is param2 (stack)
    // descriptor points to a structure with 6 DWORDs: three groups of (alignment, baseSize, count)
    // This function allocates sub-blocks and stores pointers in an array.

    uint alignedSize;
    uint alignment;
    uint count;
    uint baseSize;
    uint* descPtr;
    uint allocatedPtr;
    int accumulatedSize;
    int slotIndex;

    output[1] = someValue;
    // Modify someValue: this - 8 + someValue (seems to compute a pointer offset)
    someValue = this - 8 + someValue;
    output[3] = someValue;
    output[0] = this;
    output[2] = 2;   // number of sub-blocks
    output[4] = 0;   // flag or reserved

    slotIndex = 4;   // offset in output array for storing pointers (starts at +4)
    descPtr = (uint*)((int)descriptor + 0x10); // skip first 16 bytes? actually descriptor layout unknown
    accumulatedSize = this; // base for size accumulation

    do {
        // Read alignment (current DWORD), clamp to minimum 4
        alignedSize = *descPtr;
        if (alignedSize < 4) alignedSize = 4;

        // Read base size (previous DWORD)
        baseSize = descPtr[-1];

        // Align baseSize up to next multiple of alignedSize
        uint alignAdjust = (alignedSize - 1) & baseSize;
        uint alignedBaseSize = baseSize;
        if (alignAdjust != 0) {
            alignedBaseSize = baseSize + (alignedSize - alignAdjust);
        }

        // Read element count (next DWORD)
        count = descPtr[1];

        // Special case: if someValue == 0x20, skip allocation (maybe a flag)
        if (someValue == 0x20) {
            allocatedPtr = 0;
            someValue = 0;
        } else {
            // Allocate memory: FUN_004abe90(accumulatedSize, count * alignedBaseSize, baseSize, alignedSize)
            allocatedPtr = allocateMemory(accumulatedSize, count * alignedBaseSize, baseSize, alignedSize);
            // extraout_ECX is the modified ecx after allocation (ignored here)
            someValue = extraout_ECX; // likely this from allocator, but unused
        }

        // Update accumulated size for next allocation (virtual address or offset)
        accumulatedSize = accumulatedSize + count * alignedBaseSize;

        // Store allocated pointer in output array at slotIndex
        *(int*)(slotIndex + output[3]) = allocatedPtr;

        // Move descriptor pointer back by 12 bytes (3 DWORDs) to previous group
        descPtr = descPtr - 3;
        slotIndex = slotIndex - 4; // decrement by 4 (writes in reverse order: first at +4, then at +0)
    } while (slotIndex >= 0);
}