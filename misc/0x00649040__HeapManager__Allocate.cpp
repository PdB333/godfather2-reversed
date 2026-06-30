// FUNC_NAME: HeapManager::Allocate
// Address: 0x00649040
// Role: Custom memory allocator for EA EARS engine
// Allocates memory from a multi-bin heap with thread-safe support
// Small allocations use segregated free lists (8 bins of 0x20-byte blocks)
// Large allocations use a separate free list of full blocks
// Supports block splitting and coalescing
// Uses critical sections for thread safety

#include <windows.h> // for CRITICAL_SECTION types

struct FreeNode {
    union {
        struct {
            uint32_t size;        // +0x00: block size (including header)
            uint32_t flags;       // +0x04: low bit = used flag, rest = size? (for boundary tag)
        };
        uint32_t raw[2];          // for alignment
    };
    FreeNode* prev;              // +0x08? Actually used as temp
    FreeNode* next;              // +0x0C? 
    // Doubly linked list pointers for free list
    FreeNode* prevFree;          // +0x14
    FreeNode* nextFree;          // +0x18
};

struct Bin {
    FreeNode* head;              // +0x00 actual use?
    // 0x20 bytes total per bin - exact layout unknown
    uint32_t padding[6];         // to reach 0x18
    FreeNode* freeList;          // +0x18: pointer to first free node in this bin
};

// Heap manager structure (size unknown, but fields identified)
struct HeapManager {
    CRITICAL_SECTION cs;         // +0x00? Actually +0x1b8 is critical section
    FreeNode largeHead;          // +0x04? Actually +0x18 is head of large free list
    Bin smallBins[8];            // +0x78: each 0x20 bytes
    uint32_t minSplitSize;       // +0x178 threshold for splitting
    // Function pointers for OS memory management
    void* (*osAlloc)(HeapManager*, uint32_t size, uint32_t param); // +0x18c
    uint32_t osAllocParam;       // +0x194
    bool (*expandHeap)(HeapManager*, uint32_t size, uint32_t alignedSize, uint32_t param); // +0x198
    uint32_t expandParam;        // +0x19c
    uint32_t maxRetries;         // +0x1a0
    CRITICAL_SECTION* pCS;       // +0x1b8
    // ... more fields
};

// Forward declarations
uint32_t getThreadIndex(); // FUN_006492b0 - returns 0-7
void freeListPostUpdate(); // FUN_00649490

int* __thiscall HeapManager::Allocate(HeapManager* this, uint32_t requestedSize)
{
    uint32_t alignedSize;
    FreeNode* pAllocNode = nullptr;
    uint32_t retryCount = 0;
    
    // Align to 16 bytes, minimum 16
    if (requestedSize < 17) {
        alignedSize = 0x10;
    } else {
        alignedSize = (requestedSize + 0xF) & 0xFFFFFFF0;
    }
    
    // Check if we are already in a critical section (thread-local flag)
    // If flag bit 0 is clear, we are not holding the lock – use fast path
    if ((in_EAX & 1) == 0) {
        // Fast path: try to allocate from small bins (index 0-7)
        uint32_t binIndex = getThreadIndex(); // returns 0..7
        if (binIndex < 8) {
            Bin* pBin = &this->smallBins[binIndex];
            // Iterate over free nodes in this bin
            for (FreeNode* pNode = pBin->freeList; pNode != pBin; pNode = pNode->nextFree) {
                uint32_t blockSize = pNode->flags & 0xFFFFFFFE; // clear used flag
                if (alignedSize <= blockSize) {
                    // Remove from free list (double linked)
                    pNode->prevFree->nextFree = pNode->nextFree;
                    pNode->nextFree->prevFree = pNode->prevFree;
                    // Mark as used
                    pNode->flags |= 1;
                    pNode->prev = pNode->size; // Save original size? Actually = *pNode
                    // Now try to split if leftover is large enough
                    if (*(uint32_t*)((char*)this + 0x178) <= ((blockSize - alignedSize) & ~1)) {
                        // Allocate a new free block header for leftover
                        FreeNode* pNewNode = (FreeNode*)this->osAlloc(this, 0x20, this->osAllocParam);
                        if (pNewNode != nullptr) {
                            pNewNode->prevFree = pNode->prevFree; // actually +0xc? 
                            // More splitting logic
                            pNewNode->next = pNode; // offset 0x10
                            pNode->prevFree = pNewNode; // offset 0x4?
                            pNewNode->size = pNode->size;
                            pNewNode->flags = (pNewNode->flags & 1) ^ (blockSize - alignedSize);
                            alignedSize = (pNode->flags & 1) ^ alignedSize;
                            pNode->flags = alignedSize;
                            pNewNode->flags &= 0xFFFFFFFE;
                            freeListPostUpdate();
                        }
                    }
                    return pNode;
                }
            }
        }
    } else {
        // Slow path: searching through large free list
        for (FreeNode* pLarge = this->largeHead; pLarge != (FreeNode*)((char*)this + 4); pLarge = pLarge->nextFree) {
            for (FreeNode* pNode = pLarge->prevFree; pNode != pLarge; pNode = pNode->prevFree) {
                if ((pNode->flags & 1) == 0) { // not used
                    uint32_t blockSize = pNode->flags & 0xFFFFFFFE;
                    if (alignedSize <= blockSize) {
                        // Remove from free list
                        pNode->prevFree->nextFree = pNode->nextFree;
                        pNode->nextFree->prevFree = pNode->prevFree;
                        pNode->flags |= 1;
                        int32_t remaining = (pNode->size - alignedSize) + blockSize;
                        pNode->prev = (FreeNode*)remaining; // Actually stored in offset 0x08
                        uint32_t leftoverSize = (uint32_t)((char*)pNode->prev - (char*)pNode->size);
                        if (leftoverSize < *(uint32_t*)((char*)this + 0x178)) {
                            return pNode; // Too small to split
                        }
                        // Allocate new block header for split
                        FreeNode* pNewNode = (FreeNode*)this->osAlloc(this, 0x20, this->osAllocParam);
                        if (pNewNode == nullptr) {
                            return pNode;
                        }
                        pNewNode->prevFree = pNode->prevFree; // offset 0x0c
                        *(FreeNode**)((char*)pNode->prevFree + 0x10) = pNewNode;
                        pNewNode->next = pNode; // offset 0x10
                        uint32_t origSize = pNode->size;
                        pNode->prevFree = pNewNode; // offset 0x04?
                        pNewNode->size = origSize;
                        pNewNode->flags = (pNewNode->flags ^ leftoverSize) & 1 ^ leftoverSize;
                        pNode->size = origSize + leftoverSize;
                        alignedSize = ((-leftoverSize) ^ pNode->flags) & 1 ^ ((pNode->flags & 0xFFFFFFFE) - leftoverSize);
                        pNode->flags = alignedSize;
                        pNewNode->flags &= 0xFFFFFFFE;
                        freeListPostUpdate();
                        return pNode;
                    }
                }
            }
        }
    }
    
    // If first attempt fails, try to expand heap
    if (this->expandHeap == nullptr) {
        return nullptr;
    }
    
    retryCount++;
    if (retryCount >= *(uint32_t*)((char*)this + 0x1a0)) {
        return nullptr;
    }
    
    // Leave critical section (nested)
    int32_t csCount = *(int32_t*)(*(uint32_t*)((char*)this + 0x1b8) + 0x18);
    for (int i = 0; i < csCount; i++) {
        LeaveCriticalSection(*(LPCRITICAL_SECTION*)((char*)this + 0x1b8));
    }
    
    bool expanded = this->expandHeap(this, requestedSize, alignedSize, this->expandParam);
    
    // Re-enter critical sections
    for (int i = 0; i < csCount; i++) {
        EnterCriticalSection(*(LPCRITICAL_SECTION*)((char*)this + 0x1b8));
    }
    
    if (!expanded) {
        return nullptr;
    }
    
    goto fast_path_retry; // continue loop
}