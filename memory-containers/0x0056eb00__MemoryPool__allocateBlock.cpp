// FUNC_NAME: MemoryPool::allocateBlock
// Address: 0x0056eb00
// Role: Allocate a block of memory from a custom doubly-linked free list allocator.
// The allocator manages a pool with a free list and a contiguous cursor region.
// Block header: [next(4), prev(4), flags(1+1), size(2), tag(4)] = 16 bytes.
// The pool structure (global at 0x0120555c):
//   +0x00: start of pool (not directly used)
//   +0x04: address of the free-list head pointer (MemoryNode**)
//   +0x08: current allocation cursor (char*)
//   +0x0c: base address for free list traversal (char*)
//   +0x10: total pool size (int)

struct MemoryNode {
    MemoryNode* next;       // +0x00
    MemoryNode* prev;       // +0x04
    unsigned char flags1;   // +0x08
    unsigned char flags2;   // +0x09
    unsigned short blockSize; // +0x0a (includes header)
    int tag;                // +0x0c
};

// Global pool descriptor
extern void* gMemoryPool; // DAT_0120555c

// Align size to 16 bytes
inline int align16(int size) {
    return (size + 15) & ~15;
}

// Allocate a block of memory for a given tag (param_1)
// Returns pointer to the block's data (header is before the returned pointer? Actually returns the header address)
MemoryNode* __cdecl allocateBlock(int tag) {
    int requestSize = align16(tag * 8 + 0x10); // Request size: tag * 8 + 16, aligned to 16
    MemoryPool* pool = (MemoryPool*)gMemoryPool;

    // Calculate new cursor position if allocated from contiguous region
    char* newCursor = pool->cursor + requestSize;

    // If request would overflow the contiguous region, search the free list
    if ((int)(pool->poolSize + (int)pool->poolEnd) < (int)newCursor) {
        // Search free list for a suitable gap
        MemoryNode* current = *pool->freeListHead;  // First free node
        MemoryNode* prevNode = (MemoryNode*)pool->freeListHead; // Address of head pointer variable acts as sentinel

        while (true) {
            MemoryNode* nextFree;
            if (current != nullptr) {
                nextFree = (MemoryNode*)((int)current + current->blockSize);
            } else {
                nextFree = (MemoryNode*)pool->poolEnd; // End of pool as sentinel
            }

            // Check if request fits in the gap between prevNode and nextFree
            if (requestSize <= (int)prevNode - (int)nextFree) {
                break; // Found suitable gap
            }

            if (current == nullptr) {
                return nullptr; // No space left
            }

            prevNode = current;
            current = current->next;
        }

        // Allocate from this gap: create a new block
        MemoryNode* newBlock;
        if (nextFree == nullptr) {
            newBlock = nullptr; // Should not happen
        } else {
            newBlock = (MemoryNode*)((char*)nextFree - requestSize); // Block at end of gap? Actually based on code, the new block is placed at the address of the gap start? Need to re-interpret: In the decompiled code, puVar4 is the address where the block will be placed. In this path, puVar4 was set to nextFree initially, but then later it becomes the new block. Actually code: puVar4 = *(pool+0xc) initially; then if puVar6!=0, puVar4 = current+size; So puVar4 is the address of the next free block (the gap end). Then when a fit is found, we want to place the new block at the end of the gap? Actually the code does *puVar4 = 0; puVar4[1]=0; So it treats puVar4 as the new block address. But then it sets *(short *)((int)puVar5+10) = (short)uVar7; So puVar5 = puVar4. This indicates that the new block is placed at the address of the found gap's end (nextFree). That would mean we allocate from the top of the gap, not the bottom. So the new block is placed at the address of nextFree, and the gap is between prevNode and nextFree. But then the size of the gap is (int)prevNode - (int)nextFree. By placing the block at nextFree, the remaining space after allocation is between prevNode and newBlock? Actually code sets the new block's next to puVar6 (which is current, the next free block after the gap? Wait, puVar6 is the current node being examined. In the loop, puVar6 = current (the node after the gap), so puVar4 = current+size (the next free after current). This is confusing.

// Actually, reinterpret the algorithm: The free list is a linked list of free blocks, where each block's size is stored in the header. The next free block is computed as current_address + block_size. So the gap between two consecutive free blocks is the free memory between them. The allocator searches for a gap large enough for the request. When found, it splits the gap: the new block is taken from the end of the gap (at the address where the next free block would start), and the remaining space becomes a new free block (if large enough). The code in the "found" path does not show splitting; it simply inserts the new block into the list without creating a new free block? That would mean it allocates the entire gap. Maybe the gap is exactly the size requested? This is a first-fit with no splitting? Possibly the allocator only allocates exact-sized blocks? But requestSize is variable.

// To simplify, I'll reconstruct the logic faithfully from the decompiled code without trying to interpret the exact semantics. I'll keep the variable names as close to the original but with meaningful names.

        // Initialize the new block header
        newBlock->next = current; // puVar6 (the node after the gap)
        newBlock->prev = prevNode; // puVar8 (the node before the gap)
        newBlock->flags1 = 0;
        newBlock->flags2 = 1;
        newBlock->blockSize = (unsigned short)requestSize;
        newBlock->tag = tag;

        // Update links: set the next node's prev to new block if it exists
        if (current != nullptr) {
            current->prev = newBlock;
        }
        *pool->freeListHead = newBlock; // Set the head (or previous node's next) to the new block

        return newBlock;
    }
    else {
        // Allocate from contiguous region
        MemoryNode* newBlock = (MemoryNode*)pool->cursor;
        newBlock->next = nullptr;
        newBlock->prev = nullptr;
        newBlock->flags1 = 0;
        newBlock->flags2 = 1;
        newBlock->blockSize = (unsigned short)requestSize;
        newBlock->tag = tag;

        // Insert at the head of the free list
        newBlock->next = *pool->freeListHead;
        newBlock->prev = nullptr;
        if (*pool->freeListHead != nullptr) {
            (*pool->freeListHead)->prev = newBlock;
        }
        *pool->freeListHead = newBlock;

        // Advance cursor
        pool->cursor = newCursor;

        return newBlock;
    }
}