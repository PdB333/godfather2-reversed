// FUNC_NAME: HeapManager::validatePointer
uint HeapManager::validatePointer(void* ptr) {
    // +0x4e8: Pointer to critical section for thread safety
    CRITICAL_SECTION* critSec = *(CRITICAL_SECTION**)((int)this + 0x4e8);
    if (critSec != nullptr) {
        EnterCriticalSection(critSec);
        // Debug info adjustment (likely for tracking semaphore state)
        critSec[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&critSec[1].DebugInfo->Type + 1);
    }

    // +0x470: Recursion depth counter to prevent reentrancy in validation
    int oldDepth = *(int*)((int)this + 0x470);
    if (oldDepth > 1) {
        goto done;
    }
    *(int*)((int)this + 0x470) = oldDepth + 1;

    // Flags stored at offset +4 in the memory block
    uint flags = *(uint*)((int)ptr + 4);
    uint result = 0;

    if ((flags & 2) == 0) {
        // First validation path: check thread context consistency
        int threadCtx1 = getHeapContext(); // FUN_00647e60
        result = (threadCtx1 == 0) ? 1 : 0;
        if (result == 0) {
            uint alignMask = flags & 0x7ffffff8; // mask to 8-byte alignment
            int threadCtx2 = getHeapContext();
            result = (threadCtx2 != threadCtx1) ? 1 : 0;
            if (result == 0) {
                result = 0;
                if ((flags & 1) == 0) {
                    threadCtx2 = getHeapContext();
                    result = (threadCtx2 != threadCtx1) ? 1 : 0;
                    if (result != 0) goto restoreDepth;
                }
                // Check embedded header fields at align offset
                uint headerFlags = *(byte*)((int)ptr + alignMask + 4) & 1;
                uint headerAlign = *(uint*)((int)ptr + alignMask);
                if (headerFlags == 0) {
                    uint mismatch = (headerAlign != alignMask) ? 1 : 0;
                    result += mismatch;
                    if (mismatch == 0) goto flag2Check;
                } else {
                    goto flag2Check;
                }
            }
        }
    } else {
        // Second path: flags has bit 1 set – includes alignment and boundary checks
        goto secondPath;
    }

flag2Check:
    if ((flags & 2) == 0) {
        // Recheck path for flags without bit 2
        int heapCtx = getHeapContext();
        uint blockSize = *(uint*)heapCtx; // Read from heap context structure
        int* ctxPtr = (int*)blockSize;
        // +0x440: Pointer to head of memory block list
        int* listHead = *(int**)((int)this + 0x440);
        result = (heapCtx == 0) + (ptr < ctxPtr) - (ptr < (int*)(*(uint*)(heapCtx + 4) + blockSize)) +
                 (2 - ((int*)((int)ptr + alignMask) < (int*)(*(uint*)(heapCtx + 4) + blockSize)));

        if (ptr == listHead) {
            // Special handling for the head block: check sentinel links
            if (((int*)ptr[2] == ptr) && ((int*)ptr[3] == ptr)) {
                // Block is isolated (no siblings)
                result += 0;
            } else {
                result += 1;
            }
            // Additional check for small block size
            result += (flags & 0x7ffffff8) < 0x10 ? 1 : 0;
            result += ~(*(byte*)((int)ptr + 4) & 1) & 1; // invert LSB of flags byte
        } else {
            // Check free list boundaries
            uint freeListStart = *(int*)((int)this + 0x460);
            uint freeListEnd   = *(int*)((int)this + 0x464);
            if (freeListStart != freeListEnd) {
                result += (ptr < ctxPtr) ? 1 : 0;
                uint freeListEndAddr = *(uint*)(heapCtx + 4) - 0x10 + blockSize;
                if ((int*)(freeListEndAddr) > (int*)((int)ptr + alignMask) && ptr != (int*)freeListEndAddr) {
                    result += 1;
                } else {
                    result += 0;
                }
            }
        }
    } else {
secondPath:
        // Path for blocks with flag bit 2 set (possibly large or special blocks)
        int heapCtx = getHeapContext();
        // +0x4d8: Alignment mask (typically power of two minus one)
        uint alignMask = *(uint*)((int)this + 0x4d8) - 1;
        result = (heapCtx != 0) +
                 ((uint)ptr & alignMask) != 0 +
                 (((uint)ptr + (flags & 0x7ffffff8) + 0x10) & alignMask) != 0 +
                 ((uint)ptr & 7) != 0;
    }

restoreDepth:
    *(int*)((int)this + 0x470) = oldDepth;

done:
    if (critSec != nullptr) {
        critSec[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&critSec[1].DebugInfo[-1].SpareWORD + 1);
        LeaveCriticalSection(critSec);
    }
    return result;
}