// FUNC_NAME: GlobalCreate176ByteObject
// Address: 0x00831570
// Allocates a 0xB0-byte object via the global memory manager and constructs it.

#include <cstdint>

typedef uint32_t undefined4;

struct AllocationParameters {
    undefined4 flags;      // +0x00 = 2
    undefined4 alignment;  // +0x04 = 0x10 (16)
    undefined4 priority;   // +0x08 = 0
};

struct MemoryManagerVTable {
    undefined4 (*Allocate)(void* self, uint32_t size, AllocationParameters* params); // vtable slot 0
};

struct MemoryManager {
    MemoryManagerVTable* vtable;
};

// External functions
MemoryManager* GetMemoryManager();               // FUN_009c8f80
undefined4 Construct176ByteObject(void* memory); // FUN_00831330

undefined4 GlobalCreate176ByteObject(void) {
    MemoryManager* mgr = GetMemoryManager();
    AllocationParameters params;
    params.flags = 2;
    params.alignment = 0x10;
    params.priority = 0;

    void* raw = mgr->vtable->Allocate(mgr, 0xB0, &params);
    if (raw != nullptr) {
        return Construct176ByteObject(raw);
    }
    return 0;
}