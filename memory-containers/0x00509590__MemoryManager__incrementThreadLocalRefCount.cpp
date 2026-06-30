// FUNC_NAME: MemoryManager::incrementThreadLocalRefCount
char* MemoryManager::incrementThreadLocalRefCount(int slotIndex, int* pFieldOffset)
{
    // Access thread-local storage via FS:[0x2C] to get the TLS base pointer.
    // Dereference twice to obtain a global pool array pointer, then add 8 to reach the actual array.
    int* poolArray = *(int**)(*(int**)(*(int**)__readfsdword(0x2C)) + 8);
    // Each slot in the pool is 0x50 bytes.
    int* objectBase = (int*)((int)poolArray + slotIndex * 0x50);
    // The ref count is stored as a byte at offset 0x55 + the field offset provided by caller.
    int fieldOffset = *pFieldOffset;
    char* refCountPtr = (char*)objectBase + 0x55 + fieldOffset;
    // Increment the reference count byte.
    *refCountPtr = *refCountPtr + 1;
    // Return pointer to the incremented byte (cast to int in original).
    return (char*)objectBase + 0x55 + fieldOffset;
}