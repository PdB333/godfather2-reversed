// FUNC_NAME: PoolAllocator::allocateNewBlock
// Function address: 0x00536d50
// Allocates a block of 0x10-byte nodes and initializes the first as the free list head.
// Uses global allocator vtable at DAT_01194538.
void PoolAllocator::allocateNewBlock()
{
    // Local allocation parameters: flags, alignment, call context
    // These are passed to the allocator function
    struct AllocParams
    {
        int unk1 = 2;    // +0x00: allocation type flags
        int unk2 = 0x10; // +0x04: alignment or size hint
        int unk3 = 0;    // +0x08: misc
    } params;

    // Number of nodes to allocate is passed in ESI (index or count)
    int nodeCount = unaff_ESI; // e.g., number of nodes for this block

    // Use global allocator's vtable to allocate memory
    // The allocator function is the first in the vtable
    typedef void* (__fastcall *AllocFunc)(int size, AllocParams* params);
    AllocFunc alloc = *(AllocFunc*)(*(uint32*)DAT_01194538); // dereference vtable
    if (!alloc)
        return;

    // Allocate space for (nodeCount + 1) nodes of 0x10 bytes each
    uint16_t* block = (uint16_t*)alloc((nodeCount + 1) * 0x10, &params);
    if (!block)
        return;

    // Initialize the first node as the head of the free list
    // The node structure at block:
    // offset 0: uint16 index (stored as short)
    // offset 2: uint16 unknown (set to 0)
    // offset 4: padding? (4 bytes)
    // offset 8: pointer to next free node (4 bytes)
    block[0] = (uint16)nodeCount; // store the node count or index
    block[1] = 0;                 // clear some field
    // Set the next pointer (at offset 8) to point to the second node (offset 16)
    *(uint16_t**)(block + 4) = (uint16_t*)(block + 8); // actually offset 8 from block start
    // Note: block+4 in pointer arithmetic is 8 bytes from start; block+8 is 16 bytes from start
    // This chains the block into the allocator's free list
}