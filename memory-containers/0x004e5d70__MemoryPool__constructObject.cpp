// FUNC_NAME: MemoryPool::constructObject

void __thiscall MemoryPool::constructObject(int* thisPtr, undefined4 param_2, void* pSourceData)
{
    // Dereference this to get the pool base address
    int* pPoolHeader = reinterpret_cast<int*>(*thisPtr);

    // The pool has a cursor pointer at offset +0x14 which points to the next free location.
    // First, store a global vtable pointer at the current cursor location.
    *reinterpret_cast<int**>(pPoolHeader + 0x14 / sizeof(int)) = &PTR_LAB_01124b58;

    // Advance the cursor by 4 bytes (size of a pointer)
    int* pCursorPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(pPoolHeader) + 0x14);
    *pCursorPtr = *pCursorPtr + 4;

    // Re-read the pool header (or perhaps the cursor is already updated)
    pPoolHeader = reinterpret_cast<int*>(*thisPtr);

    // Store param_2 (e.g., an object ID/type) at the new cursor position
    *reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(pPoolHeader) + 0x14)) = param_2;

    // Align the cursor to a 16-byte boundary (adding 0x13 and masking lower 4 bits)
    void* pAlignedBlock = reinterpret_cast<void*>((*reinterpret_cast<int*>(reinterpret_cast<char*>(pPoolHeader) + 0x14) + 0x13) & 0xFFFFFFF0);

    // Store the aligned address back into the cursor
    *reinterpret_cast<void**>(reinterpret_cast<char*>(pPoolHeader) + 0x14) = pAlignedBlock;

    // Copy 0x30 bytes from the source data into the aligned block (object data)
    memcpy(pAlignedBlock, pSourceData, 0x30);

    // Advance the cursor past the allocated object
    *reinterpret_cast<int*>(reinterpret_cast<char*>(pPoolHeader) + 0x14) = reinterpret_cast<int>(pAlignedBlock) + 0x30;

    return;
}