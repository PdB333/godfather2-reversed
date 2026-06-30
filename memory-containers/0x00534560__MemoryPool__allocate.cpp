// FUNC_NAME: MemoryPool::allocate
void MemoryPool::allocate(int *outResult)
{
    LPCRITICAL_SECTION criticalSection;
    int allocatedPtr;
    int fallbackPtr;
    int index;
    int fsOffset;

    // Global pool manager structure
    int *poolManager = (int *)DAT_0120541c;
    criticalSection = *(LPCRITICAL_SECTION *)(poolManager + 0x1b8); // +0x1B8: critical section pointer
    index = 0;

    if (criticalSection != NULL) {
        EnterCriticalSection(criticalSection);
        // Manual lock count increment (hack to avoid recursion?)
        criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&(criticalSection[1].DebugInfo)->Type + 1);
    }

    allocatedPtr = poolAllocateMemory(poolManager, 0x90); // Allocate 144 bytes from pool
    if (allocatedPtr == 0) {
        // Allocation failed, use fallback pointer from pool manager
        if (criticalSection != NULL) {
            // Manual lock count decrement
            criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(criticalSection);
        }
        fallbackPtr = *(int *)(poolManager + 0x17c); // +0x17C: fallback pointer
    } else {
        poolMarkUsed(); // Mark the allocated block as used
        fallbackPtr = *(int *)(allocatedPtr + 8); // +0x08: some field in allocated block
        if (criticalSection != NULL) {
            // Manual lock count decrement
            criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(criticalSection);
        }
    }

    // Compute index relative to global pool base
    if (fallbackPtr != 0) {
        index = fallbackPtr - DAT_01205410; // DAT_01205410: base address of pool
        // Check thread-local storage condition (FS:[0x2C] -> TLS pointer)
        int *tlsPtr = *(int **)(*(int *)(__readfsdword(0x2C)) + 8); // Dereference TLS
        if (tlsPtr + index != 0) {
            poolErrorHandler(); // FUN_00533ab0 - handle error or notify
        }
    }

    outResult[0] = index;
    outResult[1] = 1; // Always set to 1 (success flag)
}