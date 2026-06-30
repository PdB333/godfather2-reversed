// FUNC_NAME: TextureAllocator::allocateResource
uint __cdecl TextureAllocator::allocateResource(void* dataPtr, uint flags, int width, int height, int mipLevels, uint desiredIndex)
{
    uint slotIndex;
    byte* slotPtr;
    int shiftCount;
    int w, h;

    // Auto-compute mip levels if not specified
    if (mipLevels == 0) {
        mipLevels = 1;
        w = width;
        h = height;
        while (true) {
            w >>= 1;
            h >>= 1;
            if (w == 0 && h == 0) break;
            mipLevels++;
        }
    }

    // Determine slot index
    slotIndex = desiredIndex;
    if (desiredIndex == 0xFFFFFFFF) {
        slotIndex = allocateNewIndex(); // FUN_00606b50
    }

    // Validate index range
    if (slotIndex < 0x1000) {
        int offset = slotIndex * 0x38; // stride: 56 bytes per slot
        slotPtr = &gTextureSlots[0].state; // DAT_011a0f28

        if (slotPtr != nullptr && *slotPtr < 2) { // slot not already allocated (state 0 or 1)
            // Fill slot data
            *(uint32_t*)(&gTextureSlots[0].dataPtr + offset) = (uint32_t)dataPtr; // +0x08 from base? Actually DAT_011a0f30
            *(uint16_t*)(&gTextureSlots[0].width + offset) = (uint16_t)width; // +0x02 from base? Actually DAT_011a0f2a
            *(uint32_t*)(&gTextureSlots[0].flags + offset) = flags; // +0x0C from base? Actually DAT_011a0f34
            *(int16_t*)(&gTextureSlots[0].height + offset) = (int16_t)height; // +0x04 from base? Actually DAT_011a0f2c
            *(int8_t*)(&gTextureSlots[0].mipLevels + offset) = (int8_t)mipLevels; // +0x01 from base? Actually DAT_011a0f29

            // Check critical section and update free bitmap
            if (tryEnterCriticalSection()) { // FUN_00618640 - likely returns true if can acquire
                uint bitmapIndex = slotIndex >> 6;
                CRITICAL_SECTION cs = gFreeListCriticalSection; // DAT_011d917c
                EnterCriticalSection(cs);
                LeaveCriticalSection(cs);

                uint64_t bitMask = 1ULL << (slotIndex & 0x3F);
                gFreeBitmapLow[bitmapIndex] &= ~(uint32_t)(bitMask);
                gFreeBitmapHigh[bitmapIndex] &= ~(uint32_t)(bitMask >> 32);

                // Update next free index hint
                if (bitmapIndex == gNextFreeBitmapHint && 
                    gFreeBitmapLow[bitmapIndex] == 0 && 
                    gFreeBitmapHigh[bitmapIndex] == 0) {
                    gNextFreeBitmapHint++; // DAT_011d9128
                }

                // Mark slot as allocated
                *slotPtr = 2; // state = 2 (allocated and ready)

                // Perform post-allocation setup
                setupAllocation(slotIndex, flags & 0x3737000); // FUN_00606e60
                onAllocationCompleted(); // FUN_00606a40

                return slotIndex;
            }

            // If critical section failed, release automatically allocated index
            if (desiredIndex == 0xFFFFFFFF) {
                releaseAutoAllocatedIndex(false, 0); // FUN_006065a0 with false and 0
            }
        }
    }

    return 0xFFFFFFFF; // allocation failed
}