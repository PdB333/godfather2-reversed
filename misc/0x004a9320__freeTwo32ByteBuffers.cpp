// FUNC_NAME: freeTwo32ByteBuffers
extern void safeFree(void*& ptr, unsigned int size);  // custom deallocator, nulls pointer after free

// Frees two 32-byte buffers pointed to by an array of two pointers.
// pBuffers must point to a contiguous pair of pointers (e.g., struct member at +0x00 and +0x04).
// Common cleanup routine called from various destructors.
void freeTwo32ByteBuffers(void* pBuffers[2])
{
    void* firstPtr = pBuffers[0];   // first pointer (offset +0x00)
    safeFree(firstPtr, 0x20);       // free 32-byte allocation, null local copy

    void* secondPtr = pBuffers[1];  // second pointer (offset +0x04)
    safeFree(secondPtr, 0x20);      // free 32-byte allocation, null local copy
}