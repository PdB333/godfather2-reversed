//FUNC_NAME: MemoryPool::deallocateBlock
void __fastcall MemoryPool::deallocateBlock(int *this) {
    int *blockPtr;
    int blockSize;

    blockPtr = (int *)this[1]; // +0x04: pointer to allocated block
    this[0] = (int)&PTR_FUN_00e380e8; // set vtable to base class vtable

    if (blockPtr != nullptr) {
        blockSize = *blockPtr; // first word of block is its size
        FUN_009c8eb0(blockPtr); // free the block memory
        this[1] = 0; // clear pointer

        if (blockSize != 0) {
            // Add block size to global free list (DAT_01206880 + 0x14)
            int *freeListHead = (int *)(DAT_01206880 + 0x14);
            **(int **)(DAT_01206880 + 0x14) = (int)&PTR_LAB_01123be8; // set vtable for list node
            *freeListHead = *freeListHead + 4; // advance list pointer
            *(int *)*freeListHead = blockSize; // store size in list
            *freeListHead = *freeListHead + 4; // advance again
        }
    }

    this[2] = (int)&PTR_LAB_00e38180; // set second vtable (base class)
}