// FUNC_NAME: EARSObject::constructorWithDestructionFlag

// Function address: 0x00442010
// Role: Base object constructor with optional immediate destruction.
// Calls a global base initialization routine (likely vtable setup or memory init).
// If param_2 bit 0 is set, calls a global object destruction function to free the memory.
// Returns the this pointer for chaining.

#include <cstdint>

// Forward declarations for the global helper functions called
void performBaseInitialization();           // FUN_00442030
void performObjectDestruction(void* obj);   // FUN_009c8eb0

class EARSObject {
public:
    // Constructor with a flag controlling whether destruction is performed after initialization.
    // This pattern is typical of custom placement new / memory recyclers.
    __thiscall void* constructorWithDestructionFlag(uint8_t destroyFlag) {
        // Call base initialization (e.g., set up vtable, zero memory, etc.)
        performBaseInitialization();

        // If the low bit of destroyFlag is set, immediately schedule or perform destruction.
        // This may be used to return a "dead" object or to simulate a placement new + delete combo.
        if (destroyFlag & 1) {
            performObjectDestruction(this);
        }

        return this;
    }
};

// Note: The actual implementations of performBaseInitialization() and performObjectDestruction()
// are at addresses 0x00442030 and 0x009c8eb0 respectively.