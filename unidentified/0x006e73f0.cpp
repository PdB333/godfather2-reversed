// Address: 0x006e73f0
// Role: Allocates a new block of 3000 prelinked 8-byte nodes and adds it to the free list of an object pool.
// Class: ObjectPool (hypothesized)
void __fastcall ObjectPool::AllocateBlock(ObjectPool* this)
{
    // allocate block: 0x5dc4 bytes = 3000 nodes * 8 bytes + 4 byte header
    int* newBlock = (int*)FUN_009c8e50(0x5dc4);
    
    int* nodePtr = newBlock;
    int count = 3000;
    
    // Link nodes: each node occupies 2 ints (8 bytes).
    // Node i starts at newBlock[2*i + 1]; its 'next' pointer is at newBlock[2*i + 2].
    do {
        nodePtr[2] = (int)(nodePtr + 3); // point to next node's data (node i+1 start)
        count--;
        nodePtr += 2;                   // advance to next node's 'next' slot
    } while (count != 0);
    
    // The loop set the last node's 'next' to an out-of-bounds address (newBlock+6001).
    // Overwrite it with null to terminate the list.
    newBlock[6000] = 0;
    
    // Link the new block into the free list (singly-linked list of blocks).
    // +0x10: head pointer to the free list of blocks.
    // +0x08: pointer to the first free node (to quickly pop).
    *newBlock = *(int*)(this + 0x10);       // old block head becomes this block's 'next'
    *(int**)(this + 0x10) = newBlock;       // new block becomes the head
    *(int**)(this + 0x08) = newBlock + 1;   // first free node points to new block's first node
}