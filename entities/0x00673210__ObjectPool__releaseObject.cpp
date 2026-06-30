// FUNC_NAME: ObjectPool::releaseObject

#include <cstdint>

// Forward declaration of memory deallocator used by the engine
typedef void (*MemoryDeallocFunc)(void*);
extern MemoryDeallocFunc gMemoryDeallocator; // DAT_01206694

// Pool data shared among objects allocated from the same pool
struct PoolData {
    int field_0;          // +0x00: unknown
    int referenceCount;   // +0x04: number of active objects
    void** entries;       // +0x0C: array of pointers to allocated objects
};

// Object header (allocated immediately before the object's data)
struct ObjectHeader {
    int index;            // -0x08: slot index in the pool's entry array
    int padding;          // -0x04: may be unused or alignment
};

// __thiscall: 'this' points to the object being freed
void __thiscall ObjectPool::releaseObject(void* thisPtr) {
    if (thisPtr == nullptr) {
        return;
    }

    // Retrieve the shared pool data from offset 0 of this object
    PoolData* pool = *(PoolData**)thisPtr; // offset +0x00

    // Child object pointer at offset +0x10 (may be null)
    void* childObject = *(void**)((char*)thisPtr + 0x10);

    if (childObject != nullptr) {
        // The child object's index is stored at childObject - 8 (ObjectHeader.index)
        int childIndex = ((ObjectHeader*)childObject)[-1].index; // equivalent to *(int*)(childObject - 8)
        // Clear the child's slot in the pool's entry array
        pool->entries[childIndex] = nullptr;
        // Decrement the pool's reference count
        pool->referenceCount--;
        // Free the child object's block (allocation starts 0x10 bytes before childObject)
        gMemoryDeallocator((char*)childObject - 0x10);
    }

    // Index of this object is stored at thisPtr - 8 (ObjectHeader.index)
    int myIndex = ((ObjectHeader*)thisPtr)[-1].index; // equivalent to *(int*)((char*)thisPtr - 8)
    // Clear this object's slot in the pool
    pool->entries[myIndex] = nullptr;
    // Decrement reference count
    pool->referenceCount--;
    // Free this object's block (allocation starts 4 bytes before thisPtr)
    gMemoryDeallocator((char*)thisPtr - 4);
}