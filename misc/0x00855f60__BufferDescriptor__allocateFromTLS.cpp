// FUNC_NAME: BufferDescriptor::allocateFromTLS
int* __thiscall BufferDescriptor::allocateFromTLS(int* thisPtr, uint sizeInBlocks)
{
    // TLS heap structure (from TlsGetValue)
    struct TLSHeap {
        int** vtable;       // +0x00
        int* currentPtr;    // +0x08 (offset 8)
        // ... other fields ...
        int* limit;         // +0x2C (offset 44, index 11)
    };

    // Initialize descriptor fields
    thisPtr[0] = 0;          // +0x00: data pointer
    thisPtr[1] = 0;          // +0x04: unknown (maybe size or flags)
    thisPtr[2] = 0x80000000; // +0x08: size with high bit set (flag for "allocated"?)

    // Get thread-local heap
    TLSHeap* heap = (TLSHeap*)TlsGetValue(DAT_01139810);
    int* currentAlloc = heap->currentPtr;  // +0x08
    int blockSize = sizeInBlocks * 0x70 + 0x10; // 112 bytes per block + 16 header
    int newPtr = (int)currentAlloc + blockSize;

    // Check if we have space in the TLS heap
    if ((uint)newPtr > (uint)heap->limit) {
        // Not enough space, call custom allocator from vtable
        int (__thiscall *allocFunc)(int) = (int (__thiscall *)(int))heap->vtable[5]; // vtable+0x14
        currentAlloc = (int*)allocFunc(blockSize);
    } else {
        // Advance the heap pointer
        heap->currentPtr = (int*)newPtr;
    }

    // Set the data pointer and size
    thisPtr[0] = (int)currentAlloc;  // +0x00: allocated memory
    thisPtr[3] = (int)currentAlloc;  // +0x0C: same pointer (maybe for alignment)
    thisPtr[2] = sizeInBlocks | 0x80000000; // +0x08: store size with flag

    return thisPtr;
}