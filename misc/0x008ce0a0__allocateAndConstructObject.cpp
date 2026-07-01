// FUNC_NAME: allocateAndConstructObject
// Function at 0x008ce0a0: Allocates memory for an object of size 0xD0 (208 bytes) and constructs it.
// Uses the global MemoryManager singleton to allocate, then calls a constructor-like function.
// Returns pointer to constructed object, or 0 on allocation failure.

#include <cstdint>

// Forward declarations for called functions
class MemoryManager;
MemoryManager* getMemoryManager(); // FUN_009c8f80

// Constructor-like function for the object (size 0xD0)
// First parameter appears to be the caller's return address (or this pointer), second is a flag (0)
void* constructObject(void* callerAddr, uint32_t flag); // FUN_008cde60

// Allocation flags structure (size 12 bytes)
struct AllocationFlags {
    uint32_t type;       // +0x00: allocation type (e.g., 2 = heap)
    uint32_t alignment;  // +0x04: alignment requirement (e.g., 0x10 = 16 bytes)
    uint32_t unknown;    // +0x08: always 0 in this call
};

// Reconstructed function
void* allocateAndConstructObject() {
    // Get the global MemoryManager instance
    MemoryManager* memMgr = getMemoryManager();
    if (!memMgr) {
        return nullptr;
    }

    // Set up allocation flags: type=2, alignment=0x10, unknown=0
    AllocationFlags flags;
    flags.type = 2;
    flags.alignment = 0x10;
    flags.unknown = 0;

    // Call virtual function at vtable[0] (likely MemoryManager::allocate)
    // Parameters: size (0xD0), pointer to flags structure
    // Returns allocated memory pointer, or 0 on failure
    void* allocatedMem = reinterpret_cast<void*>(
        (*(int (**)(void*, uint32_t, AllocationFlags*))(*reinterpret_cast<void***>(memMgr))[0])(
            memMgr, 0xD0, &flags)
    );

    if (allocatedMem) {
        // Construct the object in the allocated memory
        // First argument is the return address of this function (caller's address)
        // Second argument is the unknown flag (0)
        void* obj = constructObject(__builtin_return_address(0), flags.unknown);
        return obj;
    }

    return nullptr;
}