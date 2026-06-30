// FUNC_NAME: SomeClass::initFreeList
void SomeClass::initFreeList(void)
{
    // Allocate a block of 0x2004 bytes (8196 bytes) from a custom allocator (likely a pool allocator)
    int* block = (int*)FUN_009c8e50(0x2004);
    int i = 0x3ff; // 1023 iterations
    int* current = block;

    // Link nodes in a free list. Each node is 8 bytes (2 ints).
    // The next pointer is stored at offset 8 from the node start.
    do {
        current[2] = (int)(current + 3); // point to the next node's second int? (off by alignment)
        i--;
        current = current + 2; // move to next node (8 bytes forward)
    } while (i != 0);

    // Terminate the list: set next pointer of last node to 0
    block[0x800] = 0; // offset 0x2000 (8192) from block start

    // Chain blocks: store old block pointer into new block's first int
    *block = *(int*)(this + 0x10);
    // Update this+0x10 to point to the new block
    *(int**)(this + 0x10) = block;
    // Set this+0x8 to the first free node (after the block header)
    *(int**)(this + 0x8) = block + 1;
}