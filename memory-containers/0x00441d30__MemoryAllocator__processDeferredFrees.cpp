// FUNC_NAME: MemoryAllocator::processDeferredFrees
void MemoryAllocator::processDeferredFrees() {
    // this+0x10: pointer to head of deferred free list (linked list of blocks to be freed)
    uint32* block = *(uint32**)((uint8*)this + 0x10);

    while (block != nullptr) {
        // Global allocator table: at offset 0x1c is a pointer to the active allocator
        // The allocator structure fields:
        //   +0x00: base pointer of allocated range (used for bounds check)
        //   +0x04: size of the managed region
        //   +0x08: free list head (points to first free block)
        //   +0x14: count of free blocks
        //   +0x1c: function pointer for destructor (or null if none)
        uint32* allocator = *(uint32**)(*(uint32*)0x01223428 + 0x1c);

        // base of the pool (pointer to first byte)
        uint32* base = (uint32*)*allocator;

        // Save next block pointer (stored at block[1]) and clear the LSB flag
        // (the LSB may indicate that the block is currently being freed, so we mask it out)
        uint32* next = (uint32*)(block[1] & ~1);

        if (base != nullptr) {
            // Check if block falls within the allocator's managed region.
            // If no destructor is set (allocator[7] == 0) OR block is in range, we free it.
            if (allocator[7] == 0 ||
                (base <= block && block < (uint32*)((uint8*)base + allocator[1]))) {
                // Add block to free list.
                block[0] = allocator[2];          // next = current free list head
                allocator[5]++;                   // increment free count
                allocator[2] = (uint32)block;     // free list head = this block
            } else {
                // Block is outside managed range or allocator has a destructor: call destructor.
                // vtable at allocator[7] first entry is the destructor (offset 0x8 in vtable?)
                (*(void (*)(uint32*))allocator[7])(block);
            }
        }

        block = next; // advance to next block in deferred list
    }
}