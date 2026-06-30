// FUNC_NAME: MemoryManager::allocate
// Address: 0x00649040
// Role: Custom heap allocator with bin-based free lists and thread safety (critical sections).
// This function allocates a block of memory of at least 'size' bytes from a memory pool.
// It uses 8 size bins for small allocations and a general free list for larger ones.
// If allocation fails, it may call a callback to expand the heap.

int* __thiscall MemoryManager::allocate(uint size)
{
    uint alignedSize;
    uint binIndex;
    int* block;
    int* freeBlock;
    uint blockSize;
    int* splitBlock;
    uint newSize;
    int retryCount;
    int lockCount;
    LPCRITICAL_SECTION criticalSection;
    LPCRITICAL_SECTION tempCS;
    char success;

    retryCount = 0;

    // Align size to 16 bytes, minimum 16
    if (size < 0x11) {
        alignedSize = 0x10;
    } else {
        alignedSize = (size + 0xf) & 0xfffffff0;
    }

    do {
        // Check thread-local flag (in_EAX) to decide allocation strategy
        if ((in_EAX & 1) == 0) {
            // Use bin allocation
            binIndex = getBinIndex(); // FUN_006492b0 - returns bin index (0-7)
            if (binIndex < 8) {
                // Iterate over bins starting from binIndex
                for (; binIndex < 8; binIndex++) {
                    // Each bin entry is 0x20 bytes, starting at offset 0x78 from this
                    int* binHead = (int*)((uint)this + 0x78 + binIndex * 0x20);
                    // Traverse free list in this bin
                    for (freeBlock = (int*)binHead[6]; freeBlock != binHead; freeBlock = (int*)freeBlock[6]) {
                        blockSize = freeBlock[1];
                        if (alignedSize <= (blockSize & 0xfffffffe)) {
                            // Remove block from free list
                            *(int*)(freeBlock[5] + 0x18) = freeBlock[6];
                            *(int*)(freeBlock[6] + 0x14) = freeBlock[5];
                            // Mark as allocated (set low bit)
                            freeBlock[1] = blockSize | 1;
                            // Store original size in field[2]? (maybe for coalescing)
                            freeBlock[2] = *freeBlock;
                            // Check if we can split the block
                            if ((*(uint*)(this + 0x178) <= (blockSize & 0xfffffffe) - alignedSize) &&
                                (splitBlock = (int*)((*(code**)(this + 0x18c))(this, 0x20, *(undefined4*)(this + 0x194)),
                                 splitBlock != 0)) {
                                // Split: create a new free block after the allocated part
                                splitBlock[4] = freeBlock[4];
                                *(int**)(freeBlock[4] + 0xc) = splitBlock;
                                splitBlock[3] = (int)freeBlock;
                                freeBlock[4] = (int)splitBlock;
                                *splitBlock = *freeBlock + alignedSize;
                                splitBlock[1] = (splitBlock[1] & 1) ^ ((freeBlock[1] & 0xfffffffe) - alignedSize);
                                newSize = (freeBlock[1] & 1) ^ alignedSize;
                                goto LAB_006491f5;
                            }
                            // Return the allocated block
                            return freeBlock;
                        }
                    }
                }
            }
        } else {
            // Use general free list (linked list starting at offset 0x18)
            for (int* listHead = *(int**)(this + 0x18); listHead != (int*)(this + 4); listHead = (int*)listHead[5]) {
                // Each list entry has a sublist at offset 3
                for (freeBlock = (int*)listHead[3]; freeBlock != listHead; freeBlock = (int*)freeBlock[3]) {
                    if (((freeBlock[1] & 1) == 0) && (blockSize = freeBlock[1] & 0xfffffffe, alignedSize <= blockSize)) {
                        // Remove from free list
                        *(int*)(freeBlock[5] + 0x18) = freeBlock[6];
                        *(int*)(freeBlock[6] + 0x14) = freeBlock[5];
                        // Mark allocated
                        freeBlock[1] = blockSize | 1;
                        // Calculate remaining size
                        int remaining = (*freeBlock - alignedSize) + blockSize;
                        freeBlock[2] = remaining;
                        retryCount = remaining - *freeBlock;
                        // If remaining is less than threshold, return as is
                        if (retryCount < *(uint*)(this + 0x178)) {
                            return freeBlock;
                        }
                        // Otherwise split
                        splitBlock = (int*)((*(code**)(this + 0x18c))(this, 0x20, *(undefined4*)(this + 0x194));
                        if (splitBlock == 0) {
                            return freeBlock;
                        }
                        splitBlock[3] = freeBlock[3];
                        *(int**)(freeBlock[3] + 0x10) = splitBlock;
                        splitBlock[4] = (int)freeBlock;
                        int origSize = *freeBlock;
                        freeBlock[3] = (int)splitBlock;
                        *splitBlock = origSize;
                        splitBlock[1] = (splitBlock[1] ^ retryCount) & 1 ^ retryCount;
                        *freeBlock = origSize + retryCount;
                        newSize = ((-retryCount) ^ freeBlock[1]) & 1 ^ ((freeBlock[1] & 0xfffffffe) - retryCount);
                        goto LAB_006491f5;
                    }
                }
            }
        }

        // If no block found, try to expand the heap via callback
        if (*(int*)(this + 0x198) == 0) {
            return 0;
        }
        retryCount++;
        if (*(uint*)(this + 0x1a0) <= retryCount) {
            return 0;
        }

        // Leave critical section (unlock) before calling callback
        lockCount = *(int*)(*(int*)(this + 0x1b8) + 0x18);
        int temp = lockCount;
        if (0 < temp) {
            do {
                criticalSection = *(LPCRITICAL_SECTION*)(this + 0x1b8);
                tempCS = criticalSection + 1;
                tempCS->DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&tempCS->DebugInfo[-1].SpareWORD + 1);
                LeaveCriticalSection(criticalSection);
                temp--;
            } while (temp != 0);
        }

        // Call the expansion callback
        success = (**(code**)(this + 0x198))(this, size, alignedSize, *(undefined4*)(this + 0x19c));

        // Re-enter critical section
        if (0 < lockCount) {
            do {
                tempCS = *(LPCRITICAL_SECTION*)(this + 0x1b8);
                EnterCriticalSection(tempCS);
                tempCS = tempCS + 1;
                tempCS->DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&tempCS->DebugInfo->Type + 1);
                lockCount--;
            } while (lockCount != 0);
        }

        if (success == 0) {
            return 0;
        }
    } while (true);

LAB_006491f5:
    // Common code for splitting: update block size and clear flag
    freeBlock[1] = newSize;
    splitBlock[1] = splitBlock[1] & 0xfffffffe;
    FUN_00649490(); // Debug/validation function
    return freeBlock;
}