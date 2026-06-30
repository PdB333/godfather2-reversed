// FUNC_NAME: FreeListManager::allocateBlock
// Address: 0x004cfd30
// Role: Allocates a new memory block (0x3004 bytes) and initializes an internal free list of 1024 nodes (12 bytes each), then links the block into the pool's block chain.

void FreeListManager::allocateBlock()
{
    // Allocate a new block of memory (0x3004 = 12292 bytes, enough for 1024 nodes of 12 bytes + 4 byte header)
    int *newBlock = (int *)allocateMemory(0x3004);
    if (newBlock == nullptr)
    {
        // Allocation failed – no changes made
        return;
    }

    // Initialize each node's first field (type/flag) to 0
    int *node = newBlock + 1;          // First node starts after the block header
    int count = 0x3FF;                 // 1023 iterations, but loop runs 1024 times
    do {
        *node = 0;                     // Zero first int of node
        node += 3;                     // Move to next node (12 bytes forward)
        count--;
    } while (-1 < count);             // Continues while count >= 0 (1024 iterations)

    // Build linked list: each node's third int becomes pointer to the next node's first int
    node = newBlock;                   // Start at block header (dummy first node? Actually node[3] is the first real node's next pointer)
    // Note: node[0] is the block header (pointer to previous block or null), node[1] unused, node[2] unused, node[3] = first node's next
    count = 0x3FF;                     // 1023 iterations – sets next pointers for nodes 0..1022
    do {
        node[3] = (int)(node + 4);     // Set next pointer to address of the following node's first int
        count--;
        node += 3;                     // Advance to next node
    } while (count != 0);             // Runs exactly 1023 times (off‑by‑one: node[3072] for the 1024th node remains whatever)

    // Attach the new block to the pool's block list and free list
    // +0x0C00 is the last 4 bytes of the block (offset 0x3000), stores the value from this+0x8 (likely the previous free list head?)
    newBlock[0x0C00] = *(int *)((char *)this + 8);
    // Block header (first int) stores the previous block address from this+0x10 (block chain head)
    *newBlock = *(int *)((char *)this + 0x10);
    // Update this+0x10 to point to the new block (new head of block chain)
    *(int **)((char *)this + 0x10) = newBlock;
    // Update this+0x8 to point to the first free node inside the new block (new head of free list)
    *(int **)((char *)this + 8) = newBlock + 1;
}