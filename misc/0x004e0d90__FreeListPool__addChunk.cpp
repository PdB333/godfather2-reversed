// FUNC_NAME: FreeListPool::addChunk
void __thiscall FreeListPool::addChunk(void)
{
    // Allocate a new memory block of size 0x2004 bytes (8196 bytes).
    // This will hold 0x400 (1024) nodes, each of size 8 bytes (two 32-bit words).
    int *newBlock = (int *)earMemAlloc(0x2004);

    // Initialize the free list within the new block.
    // Each node is 8 bytes; the first word (offset +0) is the "next" pointer,
    // the second word (offset +4) is either data or unused.
    // The loop sets up the linked list by making each node point to the next node's first word.
    // Note: piVar1[2] is actually the first word of the next node (since each node is 2 ints).
    // We set it to point to the second word of the current node? This is unusual.
    // Likely the list is structured so that each node points to the node's own second word? 
    // A more plausible interpretation: each node's first word stores the address of the next node's first word.
    // But the decompiled code does: piVar1[2] = (int)(piVar1 + 3). 
    // Assume piVar1 iterates over node starts, then piVar1[2] is at offset 8 which is the next node's first word.
    // And piVar1+3 is the address of the third int from current start (offset 12) which is the next node's second word.
    // This would set the next node's first word to point to its own second word? That makes no sense.
    // Given the lack of clarity, we faithfully reproduce the pointer arithmetic.
    int *current = newBlock;
    int count = 0x3ff; // 1023 iterations
    do {
        // Set the third int from current (offset 8) to point to the fourth int (offset 12).
        current[2] = (int)(current + 3);
        count--;
        current += 2; // Move to next node (8 bytes forward)
    } while (count != 0);

    // After loop, set the last node's boundary? This nulls the first word of a sentinel node at end of block.
    newBlock[0x800] = 0; // offset 0x2000 (8192) from block start

    // Link the new block into the existing free list.
    // The first node of the new block points to the old head (offset +0x10 from this).
    *newBlock = *(int *)(this + 0x10); // old head → new block's first node's first word

    // Update head to the new block (start of new list).
    *(int **)(this + 0x10) = newBlock;

    // Update tail to point to the second node of the new block (offset +4)?
    // Possibly the tail points to the last free node? But here it's set to newBlock+1.
    *(int **)(this + 0x8) = newBlock + 1;
}