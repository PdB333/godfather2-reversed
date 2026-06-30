// FUN_NAME: MemoryPool::initNewPool

void MemoryPool::initNewPool(void)
{
    int* newBlock;
    int numNodes;
    int* nodePtr;

    // Allocate memory block for pool: 0x6004 bytes (1024 nodes * 24 bytes + 4 bytes header)
    newBlock = (int*)customMalloc(0x6004);
    if (newBlock == 0) {
        return;
    }

    // Construct pool header at the start of the block (likely initializes free list pointers)
    constructPoolHeader(newBlock);

    // Initialize free list: 1024 nodes of 24 bytes each
    numNodes = 0x3FF; // 1023 (loop runs 1024 times? Actually 0x3FF iterations)
    nodePtr = newBlock + 0; // start at first node

    do {
        // Set the "next" pointer in the next node to point to nodePtr+7? 
        // This sets each node's next pointer (offset 24) to point 4 bytes into the next node
        nodePtr[6] = (int)(nodePtr + 7);
        numNodes--;
        nodePtr = nodePtr + 6; // move to next node (24 bytes forward)
    } while (numNodes != 0);

    // Set count field at offset 0x6000 (1024*24 = 0x6000) to 0, indicating all nodes free
    newBlock[0x1800] = 0;

    // Link this new block into the pool's free list
    // +0x14: head of free list (single linked list)
    // +0x0c: pointer to first free node after header
    *newBlock = *(int*)((char*)this + 0x14); // newBlock[0] gets previous head
    *(int**)((char*)this + 0x14) = newBlock; // head points to this block
    *(int**)((char*)this + 0x0c) = newBlock + 1; // free list pointer starts at second int (after header)
}