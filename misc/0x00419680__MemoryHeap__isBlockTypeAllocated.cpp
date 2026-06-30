// FUNC_NAME: MemoryHeap::isBlockTypeAllocated
#include <intrin.h>

bool __thiscall MemoryHeap::isBlockTypeAllocated(void* thisPtr)
{
    int blockOffset = *(int*)((char*)thisPtr + 0x18); // +0x18: offset into heap manager table
    // Get the heap manager base from thread-local storage (fs:[0x2c])
    DWORD* tebPtr = (DWORD*)__readfsdword(0x2c);
    DWORD* heapManagerPtr = (DWORD*)*tebPtr; // dereference TEB field
    int heapBase = *(int*)((char*)heapManagerPtr + 8); // +0x08: base address of heap manager data

    // Read 12-byte block metadata at base + 0x30 + blockOffset
    DWORD* metadataPtr = (DWORD*)(heapBase + 0x30 + blockOffset);
    DWORD metadata[3];
    metadata[0] = *metadataPtr;
    metadata[1] = metadataPtr[1];
    metadata[2] = metadataPtr[2];

    // Read additional 4-byte field at base + 0x70 + blockOffset
    DWORD extra = *(DWORD*)(heapBase + 0x70 + blockOffset);

    // Combine metadata into a structure for the check function
    // local layout: [0] = metadata[0], [4] = metadata[1], [8] = metadata[2], [12] = extra
    // Call helper to determine block type
    int result = FUN_004bdae0(&metadata); // returns type code

    return result == 2; // 2 means allocated
}