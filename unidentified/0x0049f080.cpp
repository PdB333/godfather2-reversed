// FUN_0049f080: EARSStream::~EARSStream
// Destructor for a streaming resource object. Handles deferred cleanup of pool blocks, callbacks, and child resources.
// The object holds a resource ID (at +0x80), a linked list of child objects (at +0x08), an array of callbacks (+0x8C), a callback count (+0x90), a callback function (+0xA8), a secondary buffer (+0x98),
// and a memory manager pointer (+0x9C). Flags at byte +0xAC (bit 1 indicates a pending release).

#include <cstddef>
#include <cstdint>

// Globals defined elsewhere in the module
extern void* PTR_DAT_0110bb88;      // Free list head pointer (pool)
extern void* PTR_DAT_01117bb0;      // Alternative free list head (probably for main thread)
extern void PTR_FUN_00e352ac;       // Original vtable for EARSStream
extern void PTR_LAB_00e352b4;       // Another vtable slot (base?)
extern void PTR_FUN_00e32808;       // Final vtable before cleanup
extern void PTR_LAB_00e352a4;       // Last vtable after cleanup

// Forward declarations of callees
void FUN_0049ef80();                // Called when flag bit 1 is set (maybe release child resources?)
void FUN_0049f900(void* param, int zero);  // Processes a list (likely a deferred release list)
void FUN_009c8f80();                // Returns some value (maybe thread ID or timestamp)
void FUN_00485280();                // Yield or spin wait (used in pool lock)
void FUN_0049e970();                // Final cleanup (maybe decrement ref count or mutex unlock?)

// Vtable entry indices for memory manager interface (assumed)
typedef void (*MemFreeFunc)(void* ptr, int zero);
typedef void (*MemReleaseFunc)();

struct MemoryManagerVTable {
    void* vf0;       // placeholder
    MemFreeFunc Free; // at offset +4
    // ... other
    MemReleaseFunc Release; // at offset +12
};

struct PoolBlock {
    void* vtable;          // usually points to LAB_00485300
    uint32_t someValue;    // from FUN_009c8f80
    uint32_t resourceId;   // original resource ID
    void* next;            // +12? Actually puVar5[3] is the next pointer (offset 12)
};

// Main destructor
void __fastcall EARSStream_Desctuctor(EARSStream* this_) {
    // Update vtable pointers to base class versions
    this_->vtable = &PTR_FUN_00e352ac;
    this_->field_0x04 = &PTR_LAB_00e352b4;

    // Check flag at byte offset 0xAC (since this_ is pointer to int, offset 0x2B*4 = 0xAC)
    uint8_t flags = *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(this_) + 0xAC);
    if (flags & 2) {
        FUN_0049ef80();
    }

    // Process a deferred release list (possible pending pool blocks)
    FUN_0049f900(&LAB_0049eab0, 0);

    int32_t resourceId = this_->resourceId; // offset 0x80
    if (resourceId != 0) {
        // Choose the correct global pool head based on thread context
        void** poolHeadPtr = &PTR_DAT_0110bb88;
        // Check if current thread is main thread via FS:0x2C
        if (*(int*)(*(int*)(__readfsdword(0x2C) + 0x34)) != 0) {
            // Not main thread? Actually the check is for the presence of a structure.
            poolHeadPtr = &PTR_DAT_01117bb0;
        }

        uint32_t someValue = FUN_009c8f80();

        // Wait until a free block becomes available
        while (*poolHeadPtr == nullptr) {
            FUN_00485280(); // Spin
        }

        // Dequeue a block from the free list
        PoolBlock* block = static_cast<PoolBlock*>(*poolHeadPtr);
        *poolHeadPtr = block->next; // block->next is at offset 12 (puVar5[3])
        block->next = nullptr;

        // Initialize the block
        block->vtable = &LAB_00485300;
        block->someValue = someValue;
        block->resourceId = resourceId;

        // Enqueue the block into a secondary list (maybe a pending release list)
        // poolHeadPtr[3] is head?, poolHeadPtr[4] is tail?
        void** listHead = &poolHeadPtr[3];
        void** listTail = &poolHeadPtr[4];
        if (*listTail == nullptr) {
            *listHead = block;
        } else {
            *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(*listTail) + 12) = block; // tail->next = block
        }
        *listTail = block;

        this_->resourceId = 0;
    }

    this_->resourceId = 0;   // offset 0x84
    this_->someField = 0;    // offset 0x88

    // Process callbacks if a callback function is set
    if (this_->callbackFunc != nullptr) { // offset 0xA8
        int* callbackArray = this_->callbackArray; // offset 0x8C
        int count = this_->callbackCount;          // offset 0x90
        int* end = callbackArray + count;
        for (int* it = callbackArray; it != end; ++it) {
            this_->callbackFunc(this_, *it);
        }
        this_->callbackFunc = nullptr;
    }

    // Free the callback array via memory manager
    if (this_->callbackArray != nullptr) {
        MemoryManagerVTable* mm = reinterpret_cast<MemoryManagerVTable*>(this_->memoryManager); // offset 0x9C
        mm->Free(this_->callbackArray, 0);
    }

    // Free the secondary buffer if present
    if (this_->secondaryBuffer != nullptr) { // offset 0x98
        MemoryManagerVTable* mm = reinterpret_cast<MemoryManagerVTable*>(this_->memoryManager);
        mm->Free(this_->secondaryBuffer, 0);
    }

    // Release the memory manager
    MemoryManagerVTable* mm = reinterpret_cast<MemoryManagerVTable*>(this_->memoryManager);
    mm->Release();

    // Perform final engine cleanup
    FUN_0049e970();

    // Change vtable pointer to a next base class
    this_->field_0x04 = &PTR_FUN_00e32808;

    // Clear child resources list (offset 0x08)
    void* child = this_->childList; // offset 0x08
    while (child != nullptr) {
        void* nextChild = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(child) + 4);
        // Clear first two dwords of the child block
        *reinterpret_cast<void**>(child) = nullptr;
        *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(child) + 4) = nullptr;
        child = nextChild;
    }

    // Final vtable pointer (marks object as fully destroyed)
    this_->vtable = &PTR_LAB_00e352a4;
}