// FUNC_NAME: PooledObject::deallocate

struct PoolAllocator {
    int unk0;          // +0x00
    int refCount;      // +0x04
    int unk8;          // +0x08
    int* freeList;     // +0x0C
    int unk10;         // +0x10
    int unk14;         // +0x14
    // ... up to +0x3C
    PooledObject* firstFree; // +0x3C
    // ... up to +0x74
    int deallocating;  // +0x74
};

struct PooledObject {
    int* data;         // +0x00
    int unk04;         // +0x04
    int unk08;         // +0x08
    int unk0C;         // +0x0C
    char allocated;    // +0x10
    PoolAllocator* allocator; // +0x14
};

// External free function pointer (from DAT_01206694)
extern void (*g_pfnFree)(void* p);

void __fastcall PooledObject::deallocate(PooledObject* this, void** outPtr)
{
    if (this == nullptr)
        return;

    if (outPtr != nullptr)
        *outPtr = nullptr;

    if (this->allocated != 1) {
        // Object already deallocated – check if it is the head of the free list
        if (this != this->allocator->firstFree) {
            // Unexpected state – handle error
            FUN_00673160();
            return;
        }
        this->allocator->deallocating = 1;
        return;
    }

    int* data = this->data;
    PoolAllocator* alloc = this->allocator;

    if (data != nullptr) {
        // Clear the slot in the free list (index derived from data header at -8)
        int index = *(int*)((int)data - 8);
        alloc->freeList[index] = nullptr;
        alloc->refCount--;
        g_pfnFree((void*)((int)data - 0x10));
    }

    // Clear the object's slot in the free list (index stored at this[-2])
    int objectIndex = *((int*)this - 2); // index from header preceding this
    int* slot = (int*)(alloc->freeList + objectIndex);
    *slot = nullptr;
    alloc->refCount--;

    // Free the actual allocation (header starts this[-4])
    g_pfnFree((void*)((int*)this - 4));
}