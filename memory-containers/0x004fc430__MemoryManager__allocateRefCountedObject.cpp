// FUNC_NAME: MemoryManager::allocateRefCountedObject
void MemoryManager::allocateRefCountedObject(int *outHandle)
{
    LPCRITICAL_SECTION criticalSection;
    int baseAddr = gMemoryManager;                    // DAT_0120541c - global memory manager base
    int allocatedChunk;
    int someValue;
    int threadLocalCheck;

    criticalSection = *(LPCRITICAL_SECTION *)(baseAddr + 0x1b8); // Memory manager critical section

    if (criticalSection != nullptr) {
        EnterCriticalSection(criticalSection);
        // Suspect: misuse of debug info for custom counting
        criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo->Type + 1);
    }

    allocatedChunk = FUN_00649040(baseAddr, 0xb4); // Allocate 180-byte chunk from memory manager

    if (allocatedChunk == 0) {
        // Allocation failed
        if (criticalSection != nullptr) {
            criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(criticalSection);
        }
        someValue = *(int *)(baseAddr + 0x17c); // Fallback pointer from memory manager
    } else {
        // Allocation succeeded
        FUN_006492f0();                          // Initialize allocated chunk (constructor?)
        someValue = *(int *)(allocatedChunk + 8); // Retrieve value at offset 8 of the chunk
        if (criticalSection != nullptr) {
            criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(criticalSection);
        }
    }

    // Validate via TLS and global offset
    if ((someValue != 0) &&
        (threadLocalCheck = someValue - gSomeGlobal, *(int *)(**(int **)(__readfsdword(0x2c)) + 8) + threadLocalCheck != 0))
    {
        FUN_004f9a30(); // Additional initialization or error handling
    }

    outHandle[0] = threadLocalCheck;
    outHandle[1] = 1; // Initial reference count
    return;
}