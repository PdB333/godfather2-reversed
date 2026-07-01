// FUNC_NAME: SomeManager::constructor (tentative)
// Reconstructed C++ for function at 0x008bb800
// This appears to be a constructor for a class with multiple inheritance (multiple vtable pointers).
// Base constructor called at 0x008ba220 (assumed base class initialization).
// Several vtable pointers are set at offsets 0x00, 0x3C, 0x48, 0x50, 0x54, 0x58, 0x180.
// Fields at high offsets (0x290–0x2A4) are zeroed.

class SomeManager {
    // The actual structure members are unknown; only the initialized fields are shown.
    // Vtable pointers at the specified offsets.
public:
    // Constructor: __thiscall with one parameter (likely a configuration/memory pointer)
    SomeManager* __thiscall constructor(void* param_2);
};

// Decompiled signature: undefined4 * __thiscall FUN_008bb800(undefined4 *this,undefined4 param_2)
// Returns this pointer.
SomeManager* __thiscall SomeManager::constructor(void* param_2) {
    // Call base class constructor (likely initializes base vtable and fields)
    FUN_008ba220(param_2); // Base constructor at 0x008ba220

    // Set vtable pointers
    *(void**)this = &PTR_FUN_00d7b828;                    // +0x00 primary vtable
    *(void**)((char*)this + 0x3C) = &PTR_LAB_00d7b818;   // +0x3C (offset 0x0F*4)
    *(void**)((char*)this + 0x48) = &PTR_LAB_00d7b814;   // +0x48 (offset 0x12*4)
    *(void**)((char*)this + 0x50) = &PTR_LAB_00d7b810;   // +0x50 (offset 0x14*4)
    *(void**)((char*)this + 0x54) = &PTR_LAB_00d7b7b0;   // +0x54 (offset 0x15*4)
    *(void**)((char*)this + 0x58) = &PTR_LAB_00d7b748;   // +0x58 (offset 0x16*4)
    *(void**)((char*)this + 0x180) = &PTR_LAB_00d7b734;  // +0x180 (offset 0x60*4)

    // Zero out fields at high offsets
    *(short*)((char*)this + 0x294) = 0;   // +0x294 (0xA5*4)
    *(short*)((char*)this + 0x296) = 0;   // +0x296
    *(short*)((char*)this + 0x2a0) = 0;   // +0x2A0 (0xA8*4)
    *(short*)((char*)this + 0x2a2) = 0;   // +0x2A2

    *(int*)((char*)this + 0x290) = 0;     // +0x290 (0xA4*4)
    *(int*)((char*)this + 0x298) = 0;     // +0x298 (0xA6*4)
    *(int*)((char*)this + 0x29c) = 0;     // +0x29C (0xA7*4)
    *(int*)((char*)this + 0x2a4) = 0;     // +0x2A4 (0xA9*4)

    return this;
}