// FUNC_NAME: SlabAllocator::deallocate
// Function address: 0x005d4a10
// Deallocates a memory block (object) from a slab-based pool managed by SlabAllocator.
// The slab descriptor (SlabBlock) contains a free list embedded in the objects themselves.
// When the last object in a slab is freed, the slab is destroyed (via vtable call).

class SlabBlock {
public:
    SlabBlock* prev;      // +0x00
    SlabBlock* next;      // +0x04
    void* startAddr;      // +0x08
    void* endAddr;        // +0x0C
    int usedCount;        // +0x10  // Number of currently allocated objects in this slab
};

class SlabAllocator {
public:
    // vtable at offset 0x00 (contains destructor for SlabBlock at vtable[2])
    char someFlag;        // +0x05  // If zero, allows slab destruction when empty
    int slabCount;        // +0x14  // Total number of slab descriptors in list
    SlabBlock* slabList;  // +0x1C  // Head of doubly linked list of slabs

    // Destroys a slab block; called via vtable when slab becomes empty.
    void destroySlab(SlabBlock* block) {
        (*(void (**)(SlabBlock*))(*(int*)this + 8))(block);
    }
};

// __fastcall with this in ESI, param1 unused, param2 (EDX) = pointer to deallocate
bool __fastcall SlabAllocator::deallocate(void* param1_unused, void* ptr) {
    SlabAllocator* self; // ESI (this)
    SlabBlock* slab;
    int* pUsed;

    if (ptr == nullptr) return false;

    slab = self->slabList;
    if (slab == nullptr) return false;

    // Traverse the slab list to find which slab contains ptr
    while (ptr < slab->startAddr || slab->endAddr <= ptr) {
        slab = slab->next;
        if (slab == nullptr) return false;
    }

    // Add ptr to the slab's free list (embedded in object)
    // The first 4 bytes of the object become the new free list head
    *(void**)ptr = slab->startAddr;   // *ptr = previous head
    slab->startAddr = ptr;            // new head = ptr

    pUsed = &slab->usedCount;
    (*pUsed)--;  // One less allocated object

    // If slab has no allocated objects and destruction is allowed, remove and destroy it
    if (*pUsed == 0 && self->someFlag == '\0') {
        // Unlink from doubly linked list
        if (slab->prev == nullptr) {
            self->slabList = slab->next;
        } else {
            slab->prev->next = slab->next;
        }
        if (slab->next != nullptr) {
            slab->next->prev = slab->prev;
        }
        // Destroy the slab descriptor (via allocator's vtable)
        self->destroySlab(slab);
        self->slabCount--;
    }

    return true;
}