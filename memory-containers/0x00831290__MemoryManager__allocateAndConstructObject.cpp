// FUNC_NAME: MemoryManager::allocateAndConstructObject
// Function address: 0x00831290
// Role: Allocates a game object of size 0xD0 (208 bytes) using the global memory manager,
// then calls its constructor (at 0x00830eb0). Returns constructed object pointer or nullptr.

#include <cstdint>

// Allocation descriptor passed to the memory manager (EA EARS engine style)
struct HeapAllocParams {
    uint32_t type;       // +0x00: e.g., 2 for default allocation
    uint32_t alignment;  // +0x04: e.g., 0x10 for 16-byte alignment
    uint32_t flags;      // +0x08: e.g., 0
};

// Memory manager singleton (returned by GetMemoryManager, FUN_009c8f80)
struct MemoryManager {
    // vtable pointer at offset 0
    // First vtable entry: allocate(size, params)
    void* (__thiscall* allocate)(void* self, size_t size, HeapAllocParams* params);
};

// Constructor function for the target object (at 0x00830eb0)
// __thiscall: expects this pointer in ecx, returns the object pointer
void* __thiscall ObjectConstructor(void* this);

// Global memory manager accessor (defined elsewhere)
MemoryManager* __cdecl GetMemoryManager(); // FUN_009c8f80

// Factory function
void* __cdecl CreateObjectOfSize0xD0() {
    MemoryManager* memMgr = GetMemoryManager();
    HeapAllocParams params;
    params.type = 2;
    params.alignment = 0x10;
    params.flags = 0;

    // Allocate via the memory manager's vtable function
    void* obj = memMgr->allocate(memMgr, 0xD0, &params);
    if (obj) {
        return ObjectConstructor(obj);
    }
    return nullptr;
}