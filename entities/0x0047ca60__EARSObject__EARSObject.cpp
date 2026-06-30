// FUNC_NAME: EARSObject::EARSObject
// Address: 0x0047ca60
// Role: Constructor for EARSObject (EA EARS engine base object)
// Initializes vtable pointers, sentinel fields, and subobject pointers.

#include <cstdint>

// Forward declaration of base constructor
extern void BaseObjectConstructor(uint32_t param2); // FUN_0046c590

// Global pointer values (from static data)
extern uint32_t DAT_0110ac04; // some global object pointer
extern uint32_t DAT_00e2b1a4; // another global object pointer

class EARSObject {
public:
    // Constructor
    EARSObject(uint32_t param2);

private:
    // Layout (byte offsets from this):
    // +0x00: vtable pointer (primary)
    // +0x3C: vtable pointer (interface A)
    // +0x48: vtable pointer (interface B)
    // +0x50: vtable pointer (interface C) – overwritten later
    // +0x54: uint32_t m_stateFlags?
    // +0x58: uint16_t m_halfword0?? (two halfwords at 0x58 and 0x5A)
    // +0x5C: uint32_t
    // +0x60: uint16_t + 0x62: second half
    // +0x64: uint32_t
    // +0x68: uint16_t + 0x6A: second half
    // +0x6C: sentinel1 (0xbadbadba) → later zeroed
    // +0x70: sentinel2 (0xbeefbeef) → later zeroed
    // +0x74: uint32_t
    // +0x78: uint32_t
    // +0x80..0xBC: array of 4 pointers with padding (stride 0x14 = 20 bytes)
    // +0xC0: pointer from DAT_0110ac04
    // +0xC4: sentinel1 → zeroed
    // +0xC8: sentinel2 → zeroed
    // +0xCC..0xD0: zeros
    // +0xD4..0xE4: zeros and byte
};

// Constructor implementation
EARSObject::EARSObject(uint32_t param2) {
    // Call base constructor (likely initializes some common fields)
    BaseObjectConstructor(param2);

    // Set up vtable pointers
    // Note: The decompiler shows the same offset (0x14) assigned twice;
    // we preserve both assignments as they appear in the binary.
    *(void**)(this + 0x50) = (void*)0x00e32854;   // PTR_LAB_00e32854 (first vtable assignment at +0x50)
    *(void**)(this)        = (void*)0x00e331e8;   // PTR_FUN_00e331e8 (primary vtable)
    *(void**)(this + 0x3C) = (void*)0x00e33204;   // PTR_LAB_00e33204 (interface vtable)
    *(void**)(this + 0x48) = (void*)0x00e33214;   // PTR_LAB_00e33214 (interface vtable)
    *(void**)(this + 0x50) = (void*)0x00e33218;   // PTR_LAB_00e33218 (overwrites previous +0x50)

    // Zero out halfword and word fields (indices 0x15–0x1a and their halfword subfields)
    *(uint32_t*)(this + 0x54) = 0;                 // param_1[0x15]
    *(uint16_t*)(this + 0x58) = 0;                 // low halfword of +0x58
    *(uint16_t*)(this + 0x5A) = 0;                 // high halfword of +0x58
    *(uint32_t*)(this + 0x5C) = 0;                 // param_1[0x17]
    *(uint16_t*)(this + 0x60) = 0;                 // low halfword of +0x60
    *(uint16_t*)(this + 0x62) = 0;                 // high halfword of +0x60
    *(uint32_t*)(this + 0x64) = 0;                 // param_1[0x19]
    *(uint16_t*)(this + 0x68) = 0;                 // low halfword of +0x68
    *(uint16_t*)(this + 0x6A) = 0;                 // high halfword of +0x68

    // Set sentinel markers (temporarily)
    *(uint32_t*)(this + 0x6C) = 0xbadbadba;        // param_1[0x1b]
    *(uint32_t*)(this + 0x70) = 0xbeefbeef;        // param_1[0x1c]

    // Load globals
    uint32_t uVar2 = DAT_0110ac04;                 // from data segment
    uint32_t uVar1 = DAT_00e2b1a4;                 // from data segment

    // Store pointer from global
    *(uint32_t*)(this + 0xC0) = uVar2;             // param_1[0x30]

    // More sentinels (later overwritten)
    *(uint32_t*)(this + 0xC4) = 0xbadbadba;        // param_1[0x31]
    *(uint32_t*)(this + 0xC8) = 0xbeefbeef;        // param_1[0x32]

    // Zero out fields at +0xD4..0xE4
    *(uint32_t*)(this + 0xD4) = 0;                 // param_1[0x35]
    *(uint32_t*)(this + 0xD8) = 0;                 // param_1[0x36]
    *(uint8_t*)(this + 0xDC) = 0;                  // param_1 + 0x37 (byte)
    *(uint32_t*)(this + 0xE0) = 0;                 // param_1[0x38]
    *(uint32_t*)(this + 0xE4) = 0;                 // param_1[0x39]

    // Populate array-like region at +0x80 (stride 0x14 = 20 bytes per element)
    // Pattern: pointer at offsets 0x80, 0x94, 0xA8, 0xBC; zeros in between.
    for (int i = 0; i < 4; ++i) {
        uint32_t* elemBase = (uint32_t*)(this + 0x80 + i * 20);
        elemBase[0] = uVar1;   // pointer
        elemBase[1] = 0;       // padding
        elemBase[2] = 0;
        elemBase[3] = 0;
        elemBase[4] = 0;
    }

    // Clear sentinel fields that were set above (overwrite with zero)
    *(uint32_t*)(this + 0x78) = 0;                 // param_1[0x1e]
    *(uint32_t*)(this + 0x74) = 0;                 // param_1[0x1d]
    *(uint32_t*)(this + 0x70) = 0;                 // param_1[0x1c] (overwrites sentinel)
    *(uint32_t*)(this + 0x6C) = 0;                 // param_1[0x1b] (overwrites sentinel)
    *(uint32_t*)(this + 0xD0) = 0;                 // param_1[0x34]
    *(uint32_t*)(this + 0xCC) = 0;                 // param_1[0x33]
    *(uint32_t*)(this + 0xC8) = 0;                 // param_1[0x32] (overwrites sentinel)
    *(uint32_t*)(this + 0xC4) = 0;                 // param_1[0x31] (overwrites sentinel)
}