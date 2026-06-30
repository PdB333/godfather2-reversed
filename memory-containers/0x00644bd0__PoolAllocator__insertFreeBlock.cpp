// FUNC_NAME: PoolAllocator::insertFreeBlock
// Address: 0x00644bd0
// Role: Inserts a 16-byte free block into the pool's free list, updating head pointer.
// The block header is initialized with magic constants (8,8,9) likely for debug/validation.

void __thiscall PoolAllocator::insertFreeBlock(void* thisPtr)
{
    uint head = *(uint*)((char*)thisPtr + 4) & 0x7FFFFFF8;  // +0x04: head offset (mask out flags)
    uint newHead = head - 0x10;                              // New block is 16 bytes before current head

    // Update head pointer: preserve top bit and lower 3 bits (flags), replace middle with newHead
    *(uint*)((char*)thisPtr + 4) = (*(uint*)((char*)thisPtr + 4) & 0x80000007) | newHead;

    // Initialize the new free block's fields (offsets relative to pool base)
    // Block layout (16 bytes):
    //   +0x00: next pointer (set to self, forming circular list? or unused)
    //   +0x04: magic 8
    //   +0x08: magic 8
    //   +0x0C: magic 9
    *(uint*)((char*)thisPtr + newHead) = newHead;            // +0x00: store own offset (or next)
    *(uint*)((char*)thisPtr + head - 0xC) = 8;                // +0x04 from block start
    *(uint*)((char*)thisPtr + head - 8) = 8;                  // +0x08
    *(uint*)((char*)thisPtr + head - 4) = 9;                  // +0x0C
}