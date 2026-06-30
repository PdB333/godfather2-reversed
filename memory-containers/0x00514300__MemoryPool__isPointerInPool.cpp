// FUNC_NAME: MemoryPool::isPointerInPool
bool __thiscall MemoryPool::isPointerInPool(void* thisPtr, uint ptrToCheck) {
    uint poolSize = *(uint*)thisPtr;                          // +0x00: size of this pool block
    uint baseAddr;
    uint blockSize = 0x2A0;                                   // 672 bytes per block
    uint offset;

    if (poolSize <= ptrToCheck) {
        // Get global heap base from TLS/FS segment
        int* globalHeapPtr = *(int**)(__readfsdword(0x2C));   // FS:[0x2C] -> pointer to some global struct
        baseAddr = *(int*)((char*)globalHeapPtr + 8);         // +0x08: base address of heap region
        if (poolSize != 0) {
            offset = baseAddr + poolSize;
        } else {
            offset = 0;
        }
        // Add the block contribution from the 5th field (index 4)
        offset += (*(uint*)((char*)thisPtr + 0x10)) * blockSize; // +0x10: number of blocks (or index)

        if ((offset != 0) && (ptrToCheck < (offset - baseAddr))) {
            return true;
        }
    }
    return false;
}