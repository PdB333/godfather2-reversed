// FUNC_NAME: MemoryPool::addMemoryBlock
void __fastcall MemoryPool::addMemoryBlock(int thisPtr)
{
    // Allocate 0x5dc4 bytes (24004 bytes) for a new memory block
    // Contains 3000 free nodes of 8 bytes each, plus a 4-byte terminator
    int *newBlock = (int *)FUN_009c8e50(0x5dc4); // external heap allocator

    int nodeCount = 3000;
    int *node = newBlock;

    // Initialize free list within this block:
    // Each node is 2 ints (8 bytes). The first int of each node serves as a "next" pointer.
    // Setup: node[i].next = &node[i+1].data (??? See detailed comment)
    do {
        // For current node at 'node', set the next node's 'next' field to point to its own 'data'?
        // node[2] is the third int from current node start = first int of next node.
        // node + 3 is address of the second int of next node.
        // So: nextNode->next = &nextNode->data (?)
        node[2] = (int)(node + 3);
        nodeCount--;
        node += 2; // advance to next node (8 bytes)
    } while (nodeCount != 0);

    // Zero out the last 4 bytes of the block (terminator)
    newBlock[6000] = 0;

    // Link new block into the existing free list (head at +0x10, tail maybe at +0x08)
    *newBlock = *(int *)(thisPtr + 0x10); // new block's first node points to old head
    *(int **)(thisPtr + 0x10) = newBlock; // update head to new block
    *(int **)(thisPtr + 0x08) = newBlock + 1; // update something (likely tail/current free pointer) to second int of first node
}