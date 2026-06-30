// FUNC_NAME: Entity::testCapability
// Address: 0x0072dc40
// Role: Checks if the entity has a specific capability (bitmask) via a virtual function.
// The virtual function at vtable+0x10 returns a boolean; if true, the input flag is returned, else 0.

#include <cstdint>

// Forward declaration of the vtable function type
typedef bool (__thiscall* CapabilityCheck)(void* self, uint32_t flag, int32_t* outUnused);

class Entity {
public:
    // Virtual function table pointer
    void** vtable;

    // Returns the given flag if the entity has that capability, otherwise 0.
    // The flag is typically a single-bit mask (e.g., 1, 2, 4, ...).
    uint32_t testCapability(uint32_t flag) {
        int32_t unused = 0;  // Unused output parameter
        // Call virtual function at vtable offset 0x10
        CapabilityCheck checkFunc = (CapabilityCheck)(vtable[0x10 / sizeof(void*)]);
        bool hasCapability = checkFunc(this, flag, &unused);
        // Branchless return: if hasCapability, return flag, else 0
        return (hasCapability) ? flag : 0;
    }
};