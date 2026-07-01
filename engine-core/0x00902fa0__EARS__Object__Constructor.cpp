// FUNC_NAME: EARS::Object::Constructor
// Function address: 0x00902fa0
// Role: Base object constructor with optional memory initialization (size 0xB0)

#include <cstdint>

// Forward declarations for called functions (implemented elsewhere)
void baseConstructor(void* thisPtr);                                       // FUN_00902c40 - base class constructor
void initMemory(void* ptr, uint32_t size);                                 // FUN_0043b960 - memory zero/initialization

int __thiscall EARSObjectConstructor(EARSObject* this, byte initMemoryFlag) {
    // Call base class constructor (e.g., for a parent object)
    baseConstructor(this);

    // If bit 0 of the flag is set, initialize a memory block of 0xB0 (176) bytes
    // This is likely used for dynamic object creation where the memory needs to be prepped
    if ((initMemoryFlag & 1) != 0) {
        initMemory(this, 0xB0);
    }

    // Return the this pointer as an integer (standard convention for __thiscall constructors)
    return reinterpret_cast<int>(this);
}