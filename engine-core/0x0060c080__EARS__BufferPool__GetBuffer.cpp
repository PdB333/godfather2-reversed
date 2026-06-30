// FUNC_NAME: EARS::BufferPool::GetBuffer
#include <windows.h>

// Buffer block structure (0x40 bytes)
struct PoolBlock {
    PoolBlock* next;        // +0x00
    int field_04;           // +0x04
    int field_08;           // +0x08
    int field_0C;           // +0x0C
    int field_10;           // +0x10
    int elementCount;       // +0x18
    void* data;             // +0x1C
    int capacity;           // +0x20
    int typeId;             // +0x24
    char flags_28;          // +0x28
    char used;              // +0x29
    PoolBlock* selfPtr;     // +0x2C
    void* globalPtr;        // +0x30
};

// Extern globals (from the gane)
extern bool gPoolInitialized;           // 0x00f15a3a
extern CRITICAL_SECTION gPoolCS;        // 0x012224f8
extern PoolBlock* gFreeListHead;        // 0x012224e0
extern int gPoolAllocCount;             // 0x01205854
extern PoolBlock* gPoolAllocArray[];    // 0x011e28f0
extern void* gMemoryManagerVtable;      // 0x01205868 (vtabel pointer)
extern void* gGlobalPtrSmall;           // 0x00e44658
extern void* gGlobalPtrLarge;           // 0x00e39f98

// Helper functions from the code:
PoolBlock* AllocateBlock(int size, int allocType);
void* GetBlockDataPtr(PoolBlock* block);  // 0x0060c760
void ReleaseBlockData(PoolBlock* block);  // 0x0060c7a0
void PoolPostOperation();                // 0x0060d3f0

PoolBlock* BufferPool::GetBuffer(int elementCount, void* sourceData, PoolBlock* outBlock, int typeId)
{
    int capacityNeeded = elementCount * 2;
    bool found = false;

    if (gPoolInitialized) {
        EnterCriticalSection(&gPoolCS);

        PoolBlock* current = gFreeListHead;
        while (current != nullptr) {
            PoolBlock* block = current;  // first block in free list

            // Check feasibility: not used, same type, correct capacity
            if (!block->used &&
                block->typeId == typeId &&
                block->capacity >= capacityNeeded &&
                !((elementCount * 8) / 3 <= block->capacity))  // avoid oversized reuse
            {
                found = true;
                current = block;

                if (outBlock != nullptr) {
                    // Copy block metadata to output buffer
                    outBlock->field_04 = block->field_04;
                    outBlock->field_08 = block->field_08;
                    outBlock->field_0C = block->field_0C;
                    outBlock->field_10 = block->field_10;
                    outBlock->elementCount = block->elementCount;
                    outBlock->data = block->data;
                    outBlock->capacity = block->capacity;
                    outBlock->typeId = block->typeId;
                    outBlock->flags_28 = block->flags_28;
                    outBlock->used = block->used;

                    // Keep self pointer from the original block?
                    outBlock->selfPtr = block->selfPtr;  // originally from uVar2

                    // If the block has a data pointer, release it from the pool?
                    if (block->selfPtr != nullptr) {
                        if (gMemoryManagerVtable != nullptr) {
                            (*(void (**)(void*, int))(gMemoryManagerVtable))(block->selfPtr, 0);
                        }
                        if (block != block->selfPtr) {
                            block->selfPtr = nullptr;
                        }
                    }
                }

                if (sourceData != nullptr) {
                    void* dest = GetBlockDataPtr(current);
                    memcpy(dest, sourceData, capacityNeeded);
                    ReleaseBlockData(current);
                }

                PoolPostOperation();
                outBlock = current;
                break;
            }

            // Move to next block in free list
            current = block->next;
        }

        LeaveCriticalSection(&gPoolCS);

        if (found) {
            goto return_result;
        }
    }

    // No suitable free block found – allocate a new one
    if (outBlock == nullptr) {
        // Allocate new block structure (0x40 bytes)
        int allocParams[3] = { 2, 0x10, 0 };  // { type, alignment, options }
        outBlock = (PoolBlock*)(*(void* (__stdcall**)(int, int*))gMemoryManagerVtable)(0x40, allocParams);
        outBlock->selfPtr = outBlock;
    }
    else {
        outBlock->selfPtr = nullptr;
    }

    outBlock->elementCount = elementCount;
    outBlock->capacity = capacityNeeded;

    int allocParams2[3] = { 2, 0x10, 0 };
    void* newData = (void*)(*(void* (__stdcall**)(int, int*))gMemoryManagerVtable)(capacityNeeded, allocParams2);
    outBlock->data = newData;

    if (sourceData != nullptr) {
        memcpy(newData, sourceData, capacityNeeded);
    }

    outBlock->typeId = (int)sourceData;  // store source as ID ? (likely intended differently)
    outBlock->flags_28 = 0;
    outBlock->used = 0;

    // Add to global allocation array
    EnterCriticalSection(&gPoolCS);
    gPoolAllocArray[gPoolAllocCount] = outBlock;
    gPoolAllocCount++;
    LeaveCriticalSection(&gPoolCS);

return_result:
    // Assign global pointer based on size
    if (capacityNeeded > 0x10000) {
        outBlock->globalPtr = gGlobalPtrLarge;
    }
    else {
        outBlock->globalPtr = gGlobalPtrSmall;
    }

    return outBlock;
}