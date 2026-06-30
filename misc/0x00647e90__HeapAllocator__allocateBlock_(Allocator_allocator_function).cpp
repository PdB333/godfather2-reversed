// FUNC_NAME: HeapAllocator::allocateBlock (Allocator allocator function)

int __thiscall HeapAllocator::allocate(uint *blockHeader, uint size, byte flags1, byte flags2, uint userData1, uint userData2) {
    CRITICAL_SECTION *cs = *(CRITICAL_SECTION **)(this + 0x4E8);
    if (cs != nullptr) {
        EnterCriticalSection(cs);
    }

    // If blockHeader is null and size > 0, attempt a system allocation via other functions
    if (blockHeader == nullptr) {
        if (size != 0) {
            if (FUN_006482d0(1) != 0) {  // check if system alloc allowed
                FUN_00644a80(1);           // allocate from system heap
                if (cs != nullptr) {
                    LeaveCriticalSection(cs);
                }
                return 1;
            }
        }
    }
    else if (size > 0x3F) {
        // Align size to granularity (from offset 0x4D4) and then to 16-byte boundary
        uint alignGranularity = *(uint *)(this + 0x4D4);
        if (size % alignGranularity != 0) {
            size = (size + alignGranularity - 1) & ~(alignGranularity - 1);
        }
        if ((size & 0xF) != 0) {
            size = size & 0xFFFFFFF0;
        }

        // Initialize block header at blockHeader
        *blockHeader = ((uint)blockHeader + 0x27) & 0xFFFFFFF8;   // self-relative aligned pointer
        *(byte *)(blockHeader + 0x0D) = flags1;
        *(byte *)(blockHeader + 0x0E) = flags1;
        *(byte *)(blockHeader + 0x0F) = flags2;
        *(blockHeader + 7) = (uint)(this + 0x448);   // store list head pointer? (offset 0x1C)
        blockHeader[1] = size;      // original requested size
        blockHeader[2] = size;      // aligned size
        *(byte *)(blockHeader + 3) = 0;  // flags byte
        blockHeader[4] = userData1;
        blockHeader[5] = userData2;
        blockHeader[6] = *(uint *)(this + 0x460);   // store previous head (offset 0x18 - prev pointer)

        // Link into the list: new block becomes head, old head's next points to new block
        *(uint **)(this + 0x460) = blockHeader;       // update head
        *(uint **)(blockHeader[6] + 0x1C) = blockHeader; // old head's next = new block

        // If userData1 == 0, check if memory is committed (VirtualQuery)
        if (userData1 == 0) {
            MEMORY_BASIC_INFORMATION memInfo;
            VirtualQuery(blockHeader, &memInfo, sizeof(memInfo));
            if (memInfo.State == MEM_COMMIT) {
                blockHeader[1] = 0;   // clear size if already committed? (or mark as unused)
            }
        }

        // Set up heap block headers inside the allocated region
        uint* pHeader = (uint*)*blockHeader;   // aligned start
        uint tailSize = (uint)blockHeader + size - (uint)pHeader;
        uint alignedTail = tailSize & 0x7FFFFFF8;
        uint blockSize = alignedTail - 0x10;   // size of usable payload
        pHeader[1] = (tailSize & 0x80000007) | 1 | blockSize;   // size + flags
        *pHeader = 0;    // previous block pointer? (or free list)
        *(uint*)((byte*)pHeader + (alignedTail - 0xC)) = 8;    // footer size? (small)
        *(uint*)((byte*)pHeader + blockSize) = blockSize;     // footer block size
        *(uint*)((byte*)pHeader + (alignedTail - 8)) = 8;
        *(uint*)((byte*)pHeader + (alignedTail - 4)) = 9;

        // Call internal allocator notification
        int notifyParam = (*(int *)(this + 0x440) != (int)(this + 0x30));  // check list emptiness?
        FUN_00644a80(notifyParam);

        if (cs != nullptr) {
            LeaveCriticalSection(cs);
        }
        return 1;
    }

    // Fallthrough: if conditions not met, return failure
    if (cs != nullptr) {
        LeaveCriticalSection(cs);
    }
    return 0;
}