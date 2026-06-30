// FUNC_NAME: HeapAllocator::realloc
// Address: 0x00647550
// Role: Custom heap realloc – handles null, in-place expansion, and fallback copy.

struct HeapAllocator {
    // +0x440: pointer to some free list node (e.g., last freed block)
    // +0x478: temporary flag saved during coalescing operations
};

void* __thiscall HeapAllocator::realloc(void* oldPtr, size_t newSize, uint flags) {
    // Align size to 8 bytes, minimum 16.
    size_t alignedSize;
    if (newSize + 0xB < 0x11) {
        alignedSize = 0x10;
    } else {
        alignedSize = (newSize + 0xB) & 0xFFFFFFF8;
    }

    // If old pointer is null, allocate a new block.
    if (oldPtr == nullptr) {
        return allocate(newSize, flags); // FUN_00646620
    }

    // Read the header (4 bytes before user pointer).
    uint header = *(uint*)((char*)oldPtr - 4);
    size_t oldBlockSize = header & 0x7FFFFFF8; // lower 29 bits – block size incl. header
    bool isBlockFree = (header & 2) == 0;

    if (isBlockFree) {
        // Block is not in use – try to extend or split.
        if (oldBlockSize < alignedSize) {
            // Attempt to coalesce with next block.
            int nextBlockHeaderAddr = (int)oldPtr + oldBlockSize - 8;
            int& freeListHead = *(int*)((char*)this + 0x440);

            if (nextBlockHeaderAddr == freeListHead &&
                alignedSize + 0x10 <= (*(uint*)(nextBlockHeaderAddr + 4) & 0x7FFFFFF8) + oldBlockSize) {
                // Can extend by absorbing next free block.
                *(uint*)((char*)oldPtr - 4) = (header & 0x80000007) | alignedSize;
                freeListHead = (int)oldPtr + alignedSize - 8;
                removeBlockFromFreeList(this); // FUN_00644ae0
                return oldPtr;
            }

            // Check if next block is free and can be merged.
            uint nextBlockSize = *(uint*)(nextBlockHeaderAddr + 4) & 0x7FFFFFF8;
            if ((nextBlockHeaderAddr == freeListHead) ||
                (*(byte*)(nextBlockSize + 4 + nextBlockHeaderAddr) & 1) != 0 ||
                (nextBlockSize + oldBlockSize < alignedSize)) {
                // Cannot extend – allocate a new block.
                void* newBlock = allocate(alignedSize - 7, flags); // FUN_00646620 (size slightly less)
                if (newBlock == nullptr) return nullptr;

                // Copy only if new block is not adjacent.
                if ((HeapAllocator*)((char*)newBlock - 8) != (HeapAllocator*)((int)oldPtr + oldBlockSize - 8)) {
                    uint savedFlag = *(uint*)((char*)this + 0x478);
                    *(uint*)((char*)this + 0x478) = 0;
                    size_t copySize = oldBlockSize - 4;
                    if (copySize < 0x21) {
                        // Small copy with switch-based unrolling (details omitted)
                        if ((copySize >> 2) - 1 < 8) {
                            void* dst = newBlock;
                            void* src = oldPtr;
                            switch (oldBlockSize) {
                            case 0x20:
                                *(uint*)dst = *(uint*)src;
                                *((uint*)dst + 1) = *((uint*)src + 1);
                                dst = (uint*)dst + 2;
                                src = (uint*)src + 2;
                            case 0x18:
                                *(uint*)dst = *(uint*)src;
                                *((uint*)dst + 1) = *((uint*)src + 1);
                                dst = (uint*)dst + 2;
                                src = (uint*)src + 2;
                            case 0x10:
                                *(uint*)dst = *(uint*)src;
                                *((uint*)dst + 1) = *((uint*)src + 1);
                                dst = (uint*)dst + 2;
                                src = (uint*)src + 2;
                            case 8:
                                *(uint*)dst = *(uint*)src;
                            }
                        }
                    } else {
                        memcpy(newBlock, oldPtr, copySize);
                    }
                    commitFreeListChanges(this); // FUN_00646ea0
                    *(uint*)((char*)this + 0x478) = savedFlag;
                }
                // Old block will be freed later? (allocator handles)
                return newBlock;
            }

            // Coalesce with next free block and split.
            // Remove next block from free list.
            *(int*)(*(int*)(nextBlockHeaderAddr + 8) + 0xC) = *(int*)(nextBlockHeaderAddr + 0xC);
            *(int*)(*(int*)(nextBlockHeaderAddr + 0xC) + 8) = *(int*)(nextBlockHeaderAddr + 8);
            oldBlockSize += nextBlockSize;
        }

        // Split if the remaining space is at least 16 bytes.
        size_t remaining = oldBlockSize - alignedSize;
        if (remaining < 0x10) {
            // Use entire block.
            *(uint*)((char*)oldPtr - 4) = (header & 0x80000007) | oldBlockSize;
            *(uint*)((char*)oldPtr + oldBlockSize - 4) |= 1; // set in-use flag on next block?
            return oldPtr;
        }

        // Split: keep first part, create a new free block from the remainder.
        *(uint*)((char*)oldPtr - 4) = (header & 0x80000007) | alignedSize;
        *(uint*)((char*)oldPtr + alignedSize - 4) = remaining | 1; // new free block header
        *(uint*)((char*)oldPtr + alignedSize + remaining - 4) |= 1; // mark next block's prev as in-use?
        *(uint*)((char*)oldPtr + alignedSize + remaining - 8) = remaining;

        uint savedFlag = *(uint*)((char*)this + 0x478);
        *(uint*)((char*)this + 0x478) = 0;
        commitFreeListChanges(this); // FUN_00646ea0 (insert new free block)
        *(uint*)((char*)this + 0x478) = savedFlag;

        return oldPtr;
    } else {
        // Block is in use – cannot extend in place.
        if (oldBlockSize < alignedSize + 4) {
            // Need a new block.
            void* newBlock = allocate(alignedSize - 7, flags); // FUN_00646620
            if (newBlock != nullptr) {
                memcpy(newBlock, oldPtr, oldBlockSize - 8); // copy user data
                uint savedFlag = *(uint*)((char*)this + 0x478);
                *(uint*)((char*)this + 0x478) = 0;
                // Free old block? (handled by allocator?)
                commitFreeListChanges(this); // FUN_00646ea0
                *(uint*)((char*)this + 0x478) = savedFlag;
            }
            return newBlock;
        }
        // Otherwise, block fits – return same pointer (should not happen, but keep).
        return oldPtr;
    }
}