// FUNC_NAME: MemoryPool::deallocateBlock
// Function address: 0x00638460
// Description: Deallocates a memory block from a pool. The block header at this+6 indicates if it's a large allocation.
//   If flag at +6 is 0: size = (byte at +7) * 4 + 0x18
//   else: size = (byte at +7) * 8 + 0x10
//   Calls global free function, then subtracts size from a counter at param_EDI+0x10+0x24 (total allocated memory?).

void __thiscall MemoryPool::deallocateBlock(void* this, void* param_EDI)  // this in ECX/EAX, param_EDI in EDI
{
    int totalSize;
    int* counterPtr;

    // Determine total size of the allocated block based on header
    if (*(char*)((int)this + 6) == '\0') {
        totalSize = (uint)*(byte*)((int)this + 7) * 4 + 0x18;
    } else {
        totalSize = (uint)*(byte*)((int)this + 7) * 8 + 0x10;
    }

    // Call the global memory free function (likely a custom allocator)
    g_freeFunc();  // DAT_012059e0

    // Update a memory usage counter if the second parameter is non-null
    if (param_EDI != (void*)0) {
        counterPtr = (int*)(*(int*)((int)param_EDI + 0x10) + 0x24);
        *counterPtr = *counterPtr - totalSize;
    }
}