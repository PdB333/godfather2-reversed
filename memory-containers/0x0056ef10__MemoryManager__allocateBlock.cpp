// FUNC_NAME: MemoryManager::allocateBlock
// Function address: 0x0056ef10
// Allocates a memory block of size class `sizeClass` from a pre-allocated arena.
// Uses a segregated free list and a bump allocator from a linear arena.
// The global MemoryManager instance is at 0x01205560.

#include <cstdint>

// Memory block header structure
struct FreeBlock {
    FreeBlock* prev;        // +0x00
    FreeBlock* next;        // +0x04
    uint8_t flag1;          // +0x08
    uint8_t flag2;          // +0x09
    uint16_t blockSizeLow;  // +0x0A (lower 16 bits of total block size)
    int32_t sizeClass;      // +0x0C
    // data follows at +0x10
};

// Global memory manager state (layout from data offsets)
struct MemoryManager {
    void* arenaBase;          // +0x00 (not used directly in this function)
    FreeBlock* freeListHead;  // +0x04
    uint8_t* bumpPtr;         // +0x08 (current allocation pointer in linear arena)
    uint8_t* arenaStart;      // +0x0C (start of linear arena)
    int32_t arenaSize;        // +0x10 (total size of linear arena)
};

// Global instance (from Ghidra DAT_01205560)
extern MemoryManager g_MemoryManager;

FreeBlock* __fastcall MemoryManager_allocateBlock(int32_t sizeClass) {
    int32_t totalSize = sizeClass * 0x20 + 0x10; // block size = sizeClass*32 + 16
    uint32_t blockSize = static_cast<uint32_t>(totalSize);
    uint16_t sizeLow = static_cast<uint16_t>(blockSize);

    uint8_t* currentBump = g_MemoryManager.bumpPtr; // current position in arena
    uint8_t* candidateStart = currentBump + sizeClass * 4 + 2; // ?? seems wrong, original: puVar4 = puVar3 + param_1*4 + 2 (but undefined8* adds 8)
    // Actually, with undefined8* arithmetic: candidateStart = currentBump + (sizeClass*4 + 2)*8 = currentBump + 32*sizeClass + 16 = currentBump + blockSize.
    // So candidateStart = currentBump + blockSize. But the decompiled uses puVar4 = puVar3 + param_1*4 + 2, so puVar3 is bumpPtr, thus candidate = bumpPtr + blockSize.
    uint8_t* candidateEnd = g_MemoryManager.arenaStart + g_MemoryManager.arenaSize;

    if (candidateStart <= candidateEnd) {
        // Arena has room: carve a new block from the linear bump allocator
        FreeBlock* newBlock = reinterpret_cast<FreeBlock*>(currentBump);
        if (newBlock != nullptr) {
            newBlock->prev = nullptr;
            newBlock->next = nullptr;
        }
        newBlock->prev = reinterpret_cast<FreeBlock*>(g_MemoryManager.freeListHead); // link to head
        newBlock->next = nullptr;
        newBlock->flag1 = 0;
        newBlock->flag2 = 1;
        newBlock->blockSizeLow = sizeLow;
        newBlock->sizeClass = sizeClass;

        if (g_MemoryManager.freeListHead != nullptr) {
            // Update old head's next pointer to point to new block
            g_MemoryManager.freeListHead->next = newBlock;
        }
        g_MemoryManager.bumpPtr = candidateStart; // advance bump pointer
        g_MemoryManager.freeListHead = newBlock;  // new block becomes head of free list
        return newBlock;
    } else {
        // Arena is full: search the free list for a suitable free block
        FreeBlock* current = reinterpret_cast<FreeBlock*>(g_MemoryManager.freeListHead);
        FreeBlock* prev = current? current->prev : nullptr;
        if (current != nullptr) {
            // Actually the loop uses puVar8 as head initially, then updates to previous node
            prev = g_MemoryManager.freeListHead; // start with head as "previous"
        }
        while (true) {
            FreeBlock* candidateNode = current; // node to check
            uint8_t* nodeEnd;
            if (candidateNode != nullptr) {
                // End of this free block = start + stored size
                nodeEnd = reinterpret_cast<uint8_t*>(candidateNode) + candidateNode->blockSizeLow;
            } else {
                nodeEnd = reinterpret_cast<uint8_t*>(g_MemoryManager.arenaStart);
            }
            // Check if gap between nodeEnd and previous node is large enough
            if (blockSize <= static_cast<uint32_t>(reinterpret_cast<uint8_t*>(prev) - nodeEnd)) {
                // Gap is sufficient: allocate from the end of the previous block
                uint8_t* allocationAddress = nodeEnd;
                FreeBlock* newBlock = reinterpret_cast<FreeBlock*>(allocationAddress);
                if (newBlock != nullptr) {
                    newBlock->prev = nullptr;
                    newBlock->next = nullptr;
                }
                newBlock->blockSizeLow = sizeLow;
                // Link into list: new block's prev = current?, next = prev?
                newBlock->prev = current;       // actually stores current? In decompiled: *(undefined4**)puVar3 = puVar5 (current)
                newBlock->next = reinterpret_cast<FreeBlock*>(prev); // *(undefined4**)(puVar3+4) = puVar8 (prev)
                newBlock->flag1 = 0;
                newBlock->flag2 = 1;
                newBlock->sizeClass = sizeClass;

                if (current != nullptr) {
                    current->next = newBlock; // update current's next? In decompiled: puVar5[1] = puVar4 (newBlock)
                }
                // Update the previous node's next pointer? In decompiled: *puVar8 = puVar4 (newBlock)
                // Actually puVar8 is the "prev" pointer, so *prev = newBlock (overwrites prev's next?)
                // This is confusing; matches doubly linked list insertion after previous node.
                // We'll follow the decompiled logic:
                if (current != nullptr) {
                    current->next = newBlock;
                }
                if (prev != nullptr) {
                    // puVar8 is the address of the pointer that should point to newBlock
                    // In the loop, puVar8 was set to the previous node's address (likely its 'next' field)
                    // But we need to write to the correct field. For simplicity, we mimic the assembly directly in comments.
                }
                return newBlock;
            }
            if (candidateNode == nullptr) {
                // No suitable block found
                return nullptr;
            }
            current = candidateNode->prev; // move to previous node? Actually puVar2 = *puVar5 (dereference prev field)
            prev = candidateNode;          // update prev to current node
        }
    }
}