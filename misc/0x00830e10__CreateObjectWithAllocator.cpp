// FUNC_NAME: CreateObjectWithAllocator
// Function at 0x00830e10: Allocates and constructs an object of size 0x160 using a memory allocator.
// Uses a pool allocator descriptor (type=2, alignment=0x10, flags=0) via a singleton allocator interface.
// Returns the constructed object pointer or 0 on allocation failure.

#include <cstdint>

// Forward declaration of a memory allocator interface (likely EARS::Memory::IAllocator)
class MemoryAllocator {
public:
    // Virtual allocate method: size, params pointer (type, alignment, flags)
    // Returns pointer to allocated memory or 0.
    virtual void* allocate(uint32_t size, void* params) = 0;
};

// Structure for allocation parameters (stack layout: type, alignment, flags)
struct AllocationParams {
    uint32_t type;       // +0x00: pool type (2 here)
    uint32_t alignment;  // +0x04: requested alignment (16)
    uint32_t flags;      // +0x08: allocation flags (0)
};

// Singleton getter for the memory allocator (address 0x009c8f80)
MemoryAllocator* getMemoryAllocator();

// Constructor/initializer for the allocated object (address 0x00830bf0)
// Returns the constructed object pointer (likely the same pointer).
void* constructObject(void* memory);

// Main function
uint32_t CreateObjectWithAllocator() {
    AllocationParams params;
    params.type       = 2;
    params.alignment  = 0x10;
    params.flags      = 0;

    MemoryAllocator* allocator = getMemoryAllocator();
    void* memory = allocator->allocate(0x160, &params);  // size 0x160 = 352 bytes

    if (memory != nullptr) {
        return reinterpret_cast<uint32_t>(constructObject(memory));
    }
    return 0;
}