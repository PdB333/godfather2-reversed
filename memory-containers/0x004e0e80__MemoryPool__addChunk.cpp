// FUNC_NAME: MemoryPool::addChunk
// Function address: 0x004e0e80
// Allocates a new chunk (0x3004 bytes) and initializes it as a free list of 1024 blocks (12 bytes each).
// The free list is linked via a next pointer at offset +8 in each block.
// The chunk is prepended to the pool's chunk list (head at this+0x10) and the first free block pointer is updated (this+0x08).

void MemoryPool::addChunk(void) {
    // Allocate 0x3004 bytes (12292 bytes): 4 byte chunk header + 1024 * 12 byte blocks
    char* newChunk = (char*)FUN_009c8e50(0x3004); // actual allocation function
    if (newChunk == NULL) {
        // Allocation failed – nothing to do
        return;
    }

    // Zero out the data fields (first two ints) of each 12‑byte block
    // Blocks start at offset 4 from the chunk base
    int* blockDataIter = (int*)(newChunk + 4); // points to data[0] of first block (block 0)
    for (int i = 0; i < 1024; i++) {
        blockDataIter[0] = 0; // data[0]
        blockDataIter[1] = 0; // data[1]
        blockDataIter += 3;   // advance to next block (3 ints = 12 bytes)
    }

    // Build the free list: each block's next pointer (at offset +8 within the block)
    // points to the start of the next block's data area. The last block's next is NULL.
    // Block data areas start at chunk+4.
    char* blockDataBase = newChunk + 4;
    for (int i = 0; i < 1023; i++) {
        // Set next pointer of block i to address of block i+1's data[0]
        *(int**)(blockDataBase + i * 12 + 8) = (int*)(blockDataBase + (i + 1) * 12);
    }
    // Last block (index 1023) has a null next pointer
    *(int**)(blockDataBase + 1023 * 12 + 8) = NULL;

    // Insert the new chunk at the head of the chunk list (this+0x10)
    // The chunk's first 4 bytes store the old head pointer
    *(int**)newChunk = this->headChunk;    // this+0x10
    this->headChunk = newChunk;            // this+0x10 = newChunk

    // Update the free list pointer to the first free block's data area (block 0)
    this->nextFree = (int*)(newChunk + 4);  // this+0x08
}