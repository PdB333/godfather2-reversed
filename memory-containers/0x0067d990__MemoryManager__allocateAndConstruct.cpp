// FUNC_NAME: MemoryManager::allocateAndConstruct

struct AllocationParams {
    int flags;      // +0x00
    int alignment;  // +0x04
    int extra;      // +0x08
};

#include <cstdint>

// Global getter for the singleton memory manager
MemoryManager* getMemoryManager();

// Constructs an object in the allocated memory (possibly placement new or post-allocation init)
void* constructObject(void* memory, void* returnAddress);

void* MemoryManager::allocateAndConstruct() {
    MemoryManager* mgr = getMemoryManager();
    AllocationParams params;
    params.flags = 2;          // e.g., kAllocFlagPool
    params.alignment = 0x10;   // 16-byte alignment
    params.extra = 0;          // reserved

    void* allocated = mgr->allocate(0x80, &params);  // allocate 128 bytes
    if (allocated != nullptr) {
        // call placement constructor/debug hook with the return address
        return constructObject(allocated, (void*)__builtin_return_address(0));
    }
    return nullptr;
}