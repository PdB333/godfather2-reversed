// FUNC_NAME: PoolAllocator::deallocateBlock
// Address: 0x005f7860
// This function frees a memory block back to a pooled allocator. It removes the block from the allocated list (this+0x4c),
// calls its destructor, and then either returns it to a global free page list or prepends it to the pool's internal free list.

#include <cstddef>

// Forward declaration of a helper function
void removeFromList(void* returnBuffer, void* listHead, void* node);

// Forward declaration of debug assert
void debugAssert(const char* msg = nullptr);

class PoolAllocator {
public:
    // +0x00 vtable
    // +0x04 ... (maybe size, alignment)
    // +0x34: Pointer to a list of allocated block nodes (or another management structure)
    // +0x4c: Pointer to the head of the allocated blocks linked list (actual node pointer)
    // +0x2c in global context: a global free list head (handled externally)

    // Internal structure for a block node (likely a 32-byte header)
    struct BlockNode {
        BlockNode* next;      // +0x00
        std::size_t size;     // +0x04 (size of the block or free region)
        void*     blockPtr;   // +0x08 (pointer to the actual allocated memory)
        // ... other fields up to offset +0x14 (puVar2[5]) and +0x1c (puVar2[7])
        int       freeCount;  // +0x14 (number of free blocks in a page)
        void*     pageVtable; // +0x1c (vtable pointer for page operations, if this node represents a page)
    };

    void deallocateBlock(void* pBlock) {
        // pBlock must be non-null
        if (!pBlock) return;

        // Iterate over the allocated list to find the node that owns this block
        BlockNode* listHead = *(BlockNode**)(*(uint32_t*)((char*)this + 0x4c)); // double dereference: head node pointer
        BlockNode* currentNode = listHead;
        do {
            // Assertion: if we wrap around the circular list, something is wrong
            if (currentNode == listHead) {
                debugAssert("Circular list wrap in deallocate");
            }

            // Check if this node manages the block
            if (currentNode->blockPtr == pBlock) {
                // Remove the block node from the allocated list
                removeFromList(&pBlock, (void*)((char*)this + 0x34), currentNode);
                break;
            }

            // Assertion again after the check (same condition as before)
            if (currentNode == listHead) {
                debugAssert("Circular list wrap after check");
            }
            currentNode = currentNode->next;
        } while (currentNode != listHead);

        // Call the virtual destructor on the block (vtable[0] with 0 as argument)
        (*(void (__thiscall**)(void*, int))pBlock)(pBlock, 0);

        // Global free list handling (outside this class)
        extern BlockNode* gGlobalFreeListHead; // Singleton global allocator

        BlockNode* globalList = gGlobalFreeListHead; // unaff_EBX + 0x2c (global variable)
        BlockNode* firstNode = globalList->next; // *puVar2 (dereferenced)
        if (firstNode != nullptr) {
            // Check if the block belongs to a page managed by the global free list
            if (globalList->pageVtable != nullptr) {
                // Range check: block must be within [firstNode, firstNode + globalList->size)
                if (pBlock >= firstNode && (char*)pBlock < (char*)firstNode + globalList->size) {
                    // Return the block to the page's free list via a virtual function
                    (*(void (__thiscall**)(void*, void*))(*((uint32_t*)globalList->pageVtable) + 2))(globalList->pageVtable, pBlock);
                    return;
                }
            }
            // Otherwise, prepend the block to the global free list
            *((void**)pBlock) = globalList->blockPtr; // *param_2 = puVar2[2]
            globalList->freeCount++;
            globalList->blockPtr = pBlock;
        }
    }
};

// Dummy implementation for the helper function (actual implementation elsewhere)
void removeFromList(void* returnBuffer, void* listHead, void* node) {
    // Removes 'node' from the list rooted at 'listHead', stores removed node in returnBuffer
}