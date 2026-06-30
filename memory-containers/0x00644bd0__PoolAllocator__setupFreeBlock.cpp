// FUNC_NAME: PoolAllocator::setupFreeBlock
// Address: 0x00644bd0
// Inserts a free block into a memory pool's free list.
// The pool base is `this`, with the free list head stored at offset +0x4.
// The free list head encodes flags in bits 0-2 and bit 31; the remainder is an offset into the pool.
// This function initializes a new free block at offset (alignedBlock - 0x10) and writes metadata constants 8, 8, 9.

void __thiscall PoolAllocator::setupFreeBlock(void* this) {
    uint freeListHead = *(uint*)((byte*)this + 4); // +0x4: packed free list pointer (offset + flags)
    
    // Extract the aligned pointer portion (clear low 3 bits and bit 31)
    uint alignedBlock = freeListHead & 0x7ffffff8;
    
    // Offset of the new free block: 16 bytes before the aligned block
    uint newBlockOffset = alignedBlock - 0x10;
    
    // Update the free list head: keep flags (bits 0-2 and bit 31), replace remaining bits with newBlockOffset
    *(uint*)((byte*)this + 4) = (freeListHead & 0x80000007) | newBlockOffset;

    // Write the new block offset at the start of the new block (self-referencing or linking to pool base)
    *(uint*)((byte*)this + newBlockOffset) = newBlockOffset;

    // Write initialization constants at the tail of the old aligned block
    *(uint*)((byte*)this + (alignedBlock - 0xc)) = 8;
    *(uint*)((byte*)this + (alignedBlock - 8)) = 8;
    *(uint*)((byte*)this + (alignedBlock - 4)) = 9;
}