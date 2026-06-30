// FUN_00505430: PooledObject::~PooledObject
// Function address: 0x00505430
// Role: Destructor for a pooled object (multiply-inherited) that manages
//       a free list (from global memory manager) and removes itself from
//       a doubly linked list. Multiple vtable switches indicate virtual inheritance.
//
// Object layout (derived from access pattern):
//   +0x00: vtable pointer (set sequentially to three destructor vtables)
//   +0x10: next pointer (doubly linked list)
//   +0x14: prev pointer (doubly linked list)
//   +0x24: link pointer used for deferred freeing / free list storage
//
// Global memory manager at DAT_012068e8:
//   +0x14: pointer to current free list slot (a "stack" of (typeTag, pointer) pairs)

struct PooledObject {
    void** vtable;                      // +0x00
    // ... other fields ...
    void* next;                         // +0x10
    void* prev;                         // +0x14
    void* freeLink;                     // +0x24 (stored in free list during destruction)
};

// External global (address 0x012068e8) – assumed to be a memory manager singleton
extern char g_MemoryManager[0x??];     // size unknown; we only access +0x14

void __fastcall PooledObject::~PooledObject(void* this) // this = param_1 (__fastcall with ecx)
{
    PooledObject* obj = (PooledObject*)this;
    void* linkToFree = obj->freeLink;   // save field before clearing

    // --- First destructor vtable ---
    obj->vtable = &PTR_FUN_00e37fd4;

    if (linkToFree != nullptr) {
        // Push (typeMarker, pointer) onto the free list (managed by memory manager)
        int** freeListPtr = (int**)(g_MemoryManager + 0x14);   // pointer to current slot
        // Write the type marker (used by the allocator to identify the class)
        *(void**)(*freeListPtr) = &PTR_LAB_01124ba8;
        (*freeListPtr)++;                                 // advance by 4 bytes
        // Write the pointer to be returned to the pool
        *(void**)(*freeListPtr) = linkToFree;
        (*freeListPtr)++;                                 // advance by another 4 bytes
        // Clear the field in the object
        obj->freeLink = nullptr;
    }

    // --- Second destructor vtable ---
    obj->vtable = &PTR_FUN_00e37f48;

    if (obj->next != nullptr) {
        // Remove this node from a doubly linked list (next/prev at +0x10/+0x14)
        // Assuming the list node structure has the same offsets (prev and next swapped?)
        // Based on the assembly: prev->next = next, next->prev = prev
        PooledObject* next = (PooledObject*)obj->next;    // +0x10
        PooledObject* prev = (PooledObject*)obj->prev;    // +0x14
        prev->next = next;   // *(void**)(prev + 0x10) = next
        next->prev = prev;   // *(void**)(next + 0x14) = prev
        // The code also writes null to obj->next (param_1[4] = 0) but not to prev? Actually it sets param_1[4]=0, but not prev. That's fine.
        obj->next = nullptr;
    }

    // --- Final base vtable ---
    obj->vtable = &PTR_LAB_00e37304;
}