// FUNC_NAME: EarsMemory::reallocate
// Function at 0x006279a0 - Memory reallocation/free wrapper for EA EARS allocator
// Uses ESI as 'this' (memory manager object) and global function pointers for low-level alloc/free
// Param1: oldSize (or adjustment offset), Param2: newSize (or operation code)
int EarsMemory::reallocate(int oldSize, uint newSize) {
    int *controlBlockField;
    int returnValue; // in_EAX
    int allocResult; // iVar2
    // ESI holds 'this' (memory manager instance)
    EarsMemory *thisPtr = reinterpret_cast<EarsMemory*>(unaff_ESI); // from ESI register

    if (newSize == 0) {
        // Free operation
        if (returnValue == 0) {
            return 0;
        }
        (*pfnFree)();   // DAT_012059e0 - free memory
        returnValue = 0;
    }
    else if (newSize < 0xFFFFFFFD) {
        // Normal allocation/reallocation (newSize >= 1 and <= 0xFFFFFFFC)
        returnValue = (*pfnAlloc)(); // DAT_012059dc - allocate/realloc
        if (returnValue == 0) {
            if (thisPtr == 0) {
                return 0;
            }
            allocResult = internalAlloc(); // FUN_00635a80 - fallback allocation
            return allocResult;
        }
    }
    else {
        // Special operation (newSize == 0xFFFFFFFD, 0xFFFFFFFE, or 0xFFFFFFFF)
        internalFreeOrSomething(); // FUN_00633920
    }

    if (thisPtr != 0) {
        // Access control block at thisPtr+0x10, field at +0x24
        controlBlockField = reinterpret_cast<int*>(
            *(reinterpret_cast<int*>(thisPtr) + 0x10) + 0x24
        );
        *controlBlockField = *controlBlockField - oldSize;
        *controlBlockField = *controlBlockField + newSize;
    }
    return returnValue;
}