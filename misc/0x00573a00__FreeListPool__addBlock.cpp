// FUNC_NAME: FreeListPool::addBlock
void FreeListPool::addBlock() {
    // Allocate a new pool block of size 0x204 bytes
    int* block = (int*)FUN_009c8e50(0x204); // likely operator new or pool allocator
    if (block == nullptr) {
        block = nullptr;
    } else {
        // Initialize the free list portion of the block.
        // The block layout: 
        // - First 8 bytes: header (used later for linking)
        // - Then 32 free list entries, each 16 bytes? Pattern suggests clearing at stride.
        // Actually we zero a specific pattern: each iteration zeroes 2 ints and advances 4 ints.
        // This appears to initialize a bitmap or marker for free entries.
        int* entry = block + 2; // start at offset 8
        int count = 31;
        do {
            *entry = 0;
            entry[1] = 0;
            entry += 4; // advance 16 bytes
            count--;
        } while (count >= 0);

        // Now set up the linked list of free nodes inside the block.
        // Each node appears to be 20 bytes (5 ints) but the loop advances 16 bytes.
        // Re-interpretation: The block contains 32 entries of 16 bytes each,
        // and the next pointer is at offset 16 of each entry, pointing to the start of the next entry.
        // But piVar2+5 points 20 bytes ahead, which would be the next entry's first int.
        // So each entry has a next pointer at offset 16 that points to the beginning of the next entry.
        entry = block;
        count = 31;
        do {
            // entry[4] is the 5th int (offset 16) which is the next pointer.
            // entry+5 points to the 6th int (offset 20) which is the first int of the next entry.
            entry[4] = (int)(entry + 5);
            count--;
            entry += 4; // advance 16 bytes (to the next entry's start)
        } while (count != 0);
    }

    // Link the block into the pool's free list using fields at +8 and +0x10 from this object.
    // this+8: head pointer? This+0x10: tail pointer? Or something else.
    block[0x80] = *(int*)(this + 8); // offset 0x200 stores previous block pointer?
    *block = *(int*)(this + 0x10);   // offset 0 stores next block pointer?
    *(int**)(this + 0x10) = block;   // update tail to point to this block
    *(int**)(this + 8) = block + 1;  // update head to point to block+1 (maybe first free node)
}