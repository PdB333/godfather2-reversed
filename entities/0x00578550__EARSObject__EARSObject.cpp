// FUNC_NAME: EARSObject::EARSObject
// Address: 0x00578550
// Description: Constructor with flag parameter; calls base initialization and optionally frees memory if flag bit 0 is set.

#include <cstdint>

// Forward declarations of internal functions
void EARSObject::callBaseConstructor(); // FUN_00578570 - base class init
void EARSObject::freeObjectMemory(void* obj); // FUN_009c8eb0 - deallocate/cleanup

EARSObject::EARSObject(uint8_t flags) {
    // Invoke base constructor or common initializer
    callBaseConstructor();

    // If the lowest bit of flags is set, perform memory deallocation
    if ((flags & 1) != 0) {
        freeObjectMemory(this);
    }

    // Constructor returns this pointer implicitly
}