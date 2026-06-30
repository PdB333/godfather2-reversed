// FUNC_NAME: MemoryPool::initializeBlock
// Function address: 0x00580ec0
// Role: Initializes a memory block within a pool. Aligns the given address to 16 bytes,
// then either sets up an active block or initializes free list pointers.

class MemoryPool; // forward declaration

void FUN_0057f750(uint param); // external
void FUN_00580ca0();           // external

// Represents a block in the memory pool
struct MemoryBlock {
    // +0x00: flags (0 = free, non-zero = active)
    int flags;
    // +0x04..0x19: other fields (not used here)
    // +0x1A: short size (ushort) used for alignment/size tracking
    unsigned short size;
    // +0x24: some offset (piVar2[9])
    int offset;
    // +0x28..0x3B: padding
    // +0x3C: stores param_2 (e.g., user ID or size)
    int userData;
    // +0x40: next pointer? (not directly accessed)
    // +0x44: unknown
    // +0x48: pointer to buffer start (piVar2 + 0x20)
    void* bufferStart;
    // +0x4C..0x93: more fields
    // +0x94: free list previous (piVar2[0x25])
    MemoryBlock* freeListPrev;
    // +0x98: free list next (piVar2[0x26])
    MemoryBlock* freeListNext;
    // +0x9C: some pointer (piVar2[0x27]) – used in free path
    void* freePtr;
};

// __thiscall method of MemoryPool or similar manager
void* __thiscall MemoryPool::initializeBlock(uint rawAddress, int param2) {
    // Align address to 16-byte boundary
    int alignmentOffset = 0x10 - (rawAddress & 0xf);
    if (alignmentOffset == 0x10) {
        alignmentOffset = 0;
    }
    MemoryBlock* block = (MemoryBlock*)(rawAddress + alignmentOffset);

    if (block->flags != 0) {
        // Block is already active – set user data and buffer pointer
        block->userData = param2;                    // +0x3C
        block->bufferStart = (void*)((char*)block + 0x20); // +0x48

        // Invoke buffer initializer with combined size/address
        uint combined = (uint)block->size + (uint)(block->bufferStart);
        FUN_0057f750(combined);

        return (void*)block; // actual return via ECX
    }
    else {
        // Block is free – initialize free list pointers and call generic initializer
        block->freePtr = (void*)((char*)block + 0x3C);           // +0x9C
        int freeEnd = (int)((char*)block + 0x3C) + block->offset; // +0x24
        block->freeListPrev = (MemoryBlock*)freeEnd;              // +0x94
        block->freeListNext = (MemoryBlock*)freeEnd;              // +0x98

        FUN_00580ca0();

        return (void*)block; // actual return via ECX
    }
}