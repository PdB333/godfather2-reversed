// FUNC_NAME: ObjectFactory::createObject
// Address: 0x006d2b00
// Role: Allocates a 0xF0-byte object from the heap manager and initializes it via a constructor call.
// Likely part of a custom memory manager for a specific class (e.g., a component or entity).

#include <cstdint>

// Forward declaration of the heap manager vtable structure.
struct HeapManagerVTable {
    void* (*allocate)(HeapManager* self, uint32_t size, uint32_t* params);
};

// Heap manager singleton (returned by FUN_009c8f80).
struct HeapManager {
    HeapManagerVTable* vtable;
};

// Allocation parameters: (alignment_type=2, alignment=16, flags=0).
struct AllocParams {
    uint32_t alignmentType; // +0x00: alignment strategy (e.g., 2 = power-of-two)
    uint32_t alignment;     // +0x04: requested alignment (16 bytes)
    uint32_t flags;         // +0x08: allocation flags
};

// Forward declaration of the class-specific constructor (FUN_006d1930).
// Returns the initialized object pointer (or 0 on failure).
void* __fastcall constructObject(void* objectMemory);

// External function to get the global heap manager.
HeapManager* __fastcall getHeapManager(void);

// Factory function: allocate memory and construct the object.
// param_1 is unused in this context; the actual allocation is from the heap.
int32_t __fastcall ObjectFactory::createObject(void* unused) {
    HeapManager* heapManager = getHeapManager();             // Get the global heap manager singleton.
    AllocParams allocParams = { 2, 0x10, 0 };                // Alignment type 2, 16-byte alignment, no flags.
    void* newObject = heapManager->vtable->allocate(heapManager, 0xF0, (uint32_t*)&allocParams); // Allocate 240 bytes.
    if (newObject != nullptr) {
        return constructObject(newObject);                   // Call constructor on the allocated memory.
    }
    return 0;                                                // Allocation failed.
}