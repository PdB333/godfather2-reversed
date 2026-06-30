// FUNC_NAME: MemoryPool::allocate
int __thiscall MemoryPool::allocate(undefined4 *outPointer) {
    int *poolPtr = this->someField; // in_EAX, implicit this
    uint bitCount;
    int index;
    int err;
    undefined4 stackParams[3]; // local_10, local_c, local_8
    undefined4 *allocatedBlock;

    allocatedBlock = (undefined4 *)_calloc(4, 0x40); // 64 bytes, zeroed
    if (allocatedBlock == nullptr) {
        return -2;
    }

    // Prepare allocation parameters
    stackParams[0] = 0;          // size? alignment?
    stackParams[1] = 0x40;       // alignment
    stackParams[2] = 0;          // flags

    // Compute allocation index based on bitmap from pool
    if (*poolPtr == 0) {
        index = 0;
    } else {
        // index = (count-1)*28 + number of bits set in the bitmap entry
        index = (*poolPtr - 1) * 0x1c; // 28 bytes per chunk?
        // Access bitmap array: pool->bitmapArray[poolPtr - 1]? Actually poolPtr[3] is at +12
        uint bitmapEntry = *(uint *)(poolPtr[3] + -4 + *poolPtr * 4);
        for (bitCount = bitmapEntry; bitCount != 0; bitCount >>= 1) {
            index++;
        }
    }

    // Attempt to grow or allocate from the pool
    err = FUN_00665720(index); // possibly allocateFromPool/grow
    if (err == 0) {
        err = FUN_0066c8d0(&stackParams); // internal allocation with params
        if (err == 0) {
            *outPointer = *allocatedBlock; // pass back allocated block
            FUN_00665b40(); // presumably unlock/leave critical section
            return 0;
        }
    }
    FUN_00665b40(); // cleanup on failure
    return err;
}