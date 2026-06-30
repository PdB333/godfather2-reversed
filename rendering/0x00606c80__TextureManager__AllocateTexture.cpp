// FUNC_NAME: TextureManager::AllocateTexture
// Address: 0x00606c80
// Purpose: Thread-safe texture surface allocation from a fixed-size pool (0x1000 slots).
//          Manages a bitmap-based freelist and stores data in global slot array (DAT_011a0f28).
//          Each slot is 0x38 bytes: status(1), mipLevels(1), width(2), height(2), dataPtr(4), flags(4), padding(40).
//          Bitmap at DAT_011d8f28/DAT_011d8f2c (64-bit per word) tracks occupied slots.
//          DAT_011d9128 stores the next word to scan for free slots.

uint TextureManager::AllocateTexture(uint dataPtr, uint flags, int width, int height, int mipLevels, uint requestedIndex)
{
    byte *slotPtr;
    char lockResult;
    int computedMipLevels;
    uint handle;
    int shiftedWidth, shiftedHeight;
    uint wordIndex;
    uint64 bitMask;
    CRITICAL_SECTION *criticalSection; // local_10[3] is considered a CRITICAL_SECTION ptr but used as stack copy

    // If mipLevels is 0, compute the number of mip levels from dimensions.
    if (mipLevels == 0) {
        mipLevels = 1;
        shiftedWidth = width;
        shiftedHeight = height;
        while (true) {
            shiftedWidth >>= 1;
            shiftedHeight >>= 1;
            if (shiftedWidth == 0 && shiftedHeight == 0)
                break;
            mipLevels++;
        }
    }

    // If no specific index requested, find a free slot.
    handle = requestedIndex;
    if (requestedIndex == 0xFFFFFFFF) {
        handle = FindFreeHandle(); // FUN_00606b50 — returns a slot index < 0x1000
    }

    // Validate handle range and slot availability.
    if (handle < 0x1000) {
        slotPtr = &s_textureSlots + handle * 0x38; // s_textureSlots = DAT_011a0f28
        // Slot is free if status byte < 2 (0=free, 1=reserved, 2=allocated)
        if (slotPtr != nullptr && *slotPtr < 2) {
            // Fill slot fields
            *(uint32 *)(slotPtr + 0x08) = dataPtr;          // +0x08 data pointer
            *(uint16 *)(slotPtr + 0x02) = (uint16)width;    // +0x02 width
            *(uint32 *)(slotPtr + 0x0C) = flags;            // +0x0C flags
            *(int16 *)(slotPtr + 0x04) = (int16)height;     // +0x04 height
            *(slotPtr + 0x01) = (byte)mipLevels;            // +0x01 mip count

            lockResult = AcquireLock(); // FUN_00618640 — returns nonzero on success
            if (lockResult != 0) {
                wordIndex = handle >> 6; // which 64-bit word in bitmap
                criticalSection = &g_criticalSection; // DAT_011d917c is a CRITICAL_SECTION pointer
                EnterCriticalSection(criticalSection);
                // Clear the bit for this handle in the 64-bit bitmap
                bitMask = 1ULL << (handle & 0x3F);
                // High part of bitmap: &DAT_011d8f2c[wordIndex*2]? Actually code uses two 32-bit words per entry.
                // Using 64-bit shift via __allshl simplifies to bitwise AND complement.
                s_bitmapLow[wordIndex] &= ~(uint32)bitMask;        // low dword
                s_bitmapHigh[wordIndex] &= ~(uint32)(bitMask >> 32); // high dword
                // Update next free word pointer if current word becomes zero
                if (wordIndex == s_nextFreeWord &&
                    s_bitmapLow[wordIndex] == 0 && s_bitmapHigh[wordIndex] == 0) {
                    s_nextFreeWord++; // DAT_011d9128
                }
                LeaveCriticalSection(criticalSection);
                *slotPtr = 2; // Mark slot as allocated
                InitializeTexture(handle, flags & 0x3737000); // FUN_00606e60 — maybe set texture format/size
                FinalizeAllocation(); // FUN_00606a40 — notify system
                return handle;
            }
            // Lock failed; revert if we allocated the handle ourselves
            if (requestedIndex == 0xFFFFFFFF) {
                ReleaseLockOnFailure(lockResult != 0, 0); // FUN_006065a0 — probably frees the handle
            }
        }
    }
    return 0xFFFFFFFF; // Failure
}