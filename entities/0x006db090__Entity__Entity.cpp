// FUNC_NAME: Entity::Entity
// Function address: 0x006db090
// Role: Constructor with optional heap allocation and virtual initialization

// This constructor calls the base class constructor first.
// If the flag (param_2) has bit 0 set, it allocates a block of memory (size 0x1c0)
// and then calls a virtual function (at vtable offset 4) on the allocated memory,
// passing the current object (this) and the allocation size as arguments.
// The function returns the current object (this).

#include <cstdint>

// Forward declarations for called functions
void __thiscall BaseClassConstructor(void* thisPtr); // FUN_006da8c0
void* __cdecl allocateMemory(uint32_t size);         // FUN_009c8f80

class Entity {
public:
    // Virtual table pointer at offset 0
    // Virtual function at vtable+4: void __thiscall initializeFrom(void* thisPtr, void* source, uint32_t size);

    // Constructor
    // @param flags: bit 0 = allocate and initialize a copy (or related object)
    void* __thiscall Entity(uint8_t flags) {
        // Step 1: Call base class constructor
        BaseClassConstructor(this);

        // Step 2: If allocation flag is set, allocate memory and call a virtual initializer
        if (flags & 1) {
            void* allocated = allocateMemory(0x1c0); // Allocate 448 bytes
            // Call virtual function at vtable offset 4 on the allocated object
            // The function receives the current object (this) and the allocation size
            (*(void (__thiscall**)(void*, void*, uint32_t))(*((uint32_t*)allocated) + 4))(allocated, this, 0x1c0);
        }

        return this;
    }
};