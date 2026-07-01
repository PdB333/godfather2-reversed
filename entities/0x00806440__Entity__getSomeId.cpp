// FUNC_NAME: Entity::getSomeId
// Function at 0x00806440: Returns a value from an internal pointer or a global default.
// The 'this' pointer is passed in ECX (fastcall convention with param_1 as ECX).
// The function checks if a pointer at offset 0x1ed8 from 'this' is non-null,
// and if so, returns the value at offset 0x8 from that pointer.
// Otherwise, it returns the global default value at _DAT_00000050 (likely 0 or a sentinel).

// Note: The calling convention is __fastcall with the first parameter in ECX,
// which is typical for __thiscall in MSVC when the function is not a class member
// but uses a 'this' pointer. We'll treat it as a member function.

// The global _DAT_00000050 is likely a constant (e.g., 0 or -1) used as a default.
// We'll assume it's 0 for now, but it could be something else.

// The offset 0x1ed8 suggests this is a large class (e.g., Entity or similar).
// The pointer at +0x1ed8 might be a sub-object or a data block.
// The value at +0x8 from that pointer is likely an ID or index.

// Based on the many callers (many from functions in the 0x007xxxxx range,
// which are likely game logic functions), this is probably a frequently used
// getter for some kind of identifier.

// We'll name it getSomeId for now, but it could be getFamilyId, getPlayerId, etc.

// The return type is undefined4 (32-bit), so we'll use uint32_t.

#include <cstdint>

uint32_t Entity::getSomeId() {
    // Check if the pointer at offset 0x1ed8 is valid
    if (this->somePointer != nullptr) {
        // Return the value at offset 0x8 from that pointer
        return this->somePointer->id;
    }
    // Return the global default value (likely 0)
    return 0; // _DAT_00000050
}