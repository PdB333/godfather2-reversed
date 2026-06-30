// FUNC_NAME: GameObject::GameObject

#include <cstdint>

// Reconstructed constructor for class GameObject at 0x0075ba20
// This function appears to be a constructor that:
// - Calls a base class constructor (FUN_004ac120)
// - Sets up multiple vtable pointers for multiple inheritance
// - Zeroes many fields (likely member variables)
// - Initializes callback function pointers (64-bit pairs of address + context)
// - Adjusts internal pointer offsets based on a self-referential field (offset 0x48)
// - Frees any pre-existing sub-objects pointed to by certain fields
// - Returns the 'this' pointer

uint32_t* __thiscall GameObject::GameObject(
    uint32_t* this,
    uint32_t arg2,
    uint32_t arg3
)
{
    int* piVar1;
    int* piVar2;
    uint32_t uVar3;
    int iVar4;
    int iVar5;
    uint32_t uStack_c;
    uint32_t local_8;

    // Call base class constructor (likely from a parent class)
    FUN_004ac120(arg2, arg3);

    // Set vtable pointers for multiple inheritance / interfaces
    this[0x14] = &PTR_FUN_00e32808;   // +0x50: vtable for first interface
    iVar5 = 0;
    this[0x15] = 0;                    // +0x54
    *this = &PTR_LAB_00d6515c;         // +0x00: primary vtable
    this[0x14] = &PTR_LAB_00d65158;    // +0x50: override with different vtable (possible second interface)

    // Zero many member variables
    this[0x20] = 0;                    // +0x80
    this[0x22] = 0;                    // +0x88
    this[0x27] = 0;                    // +0x9C
    this[0x28] = 0;                    // +0xA0
    this[0x29] = 0;                    // +0xA4
    this[0x2a] = 0;                    // +0xA8
    this[0x2b] = 0;                    // +0xAC
    this[0x2c] = 0;                    // +0xB0
    this[0x2e] = 0;                    // +0xB8
    this[0x2f] = 0;                    // +0xBC
    this[0x30] = 0;                    // +0xC0
    this[0x31] = 0;                    // +0xC4
    this[0x32] = 0;                    // +0xC8
    this[0x33] = 0;                    // +0xCC
    this[0x34] = 0;                    // +0xD0

    piVar1 = (int*)(this + 0x27);      // pointer to field at +0x9C
    piVar2 = (int*)(this + 0x2e);      // pointer to field at +0xB8

    // Initialize callback function pairs (64-bit values storing function address and context)
    // These might be event handlers or delegates.
    *(uint64_t*)(this + 0x37) = ((uint64_t)(uintptr_t)&LAB_0075b560 << 32) | (uint64_t)(uintptr_t)this; // +0xDC
    *(uint64_t*)(this + 0x39) = (uint64_t)uStack_c << 32;                                           // +0xE4 (upper 32 bits from stack)
    *(uint64_t*)(this + 0x3b) = ((uint64_t)(uintptr_t)&LAB_0075b6b0 << 32) | (uint64_t)(uintptr_t)local_8; // +0xEC
    *(uint64_t*)(this + 0x3d) = ((uint64_t)(uintptr_t)&LAB_0075b580 << 32) | (uint64_t)(uintptr_t)this; // +0xF4
    *(uint64_t*)(this + 0x3f) = (uint64_t)uStack_c << 32;                                           // +0xFC
    *(uint64_t*)(this + 0x41) = ((uint64_t)(uintptr_t)&LAB_0075b6b0 << 32) | (uint64_t)(uintptr_t)local_8; // +0x104

    // More zeroing and copying
    this[0x16] = 0;                    // +0x58
    this[0x17] = 0;                    // +0x5C
    this[0x18] = 0;                    // +0x60
    *(uint64_t*)(this + 0x19) = *(uint64_t*)(this + 0x16); // copy 8 bytes from +0x58 to +0x64

    uVar3 = DAT_00d5ccf8;              // global default value
    this[0x1c] = DAT_00d5ccf8;         // +0x70
    this[0x1d] = uVar3;                // +0x74 (same as above)
    uVar3 = _DAT_00d5cf70;
    this[0x1b] = this[0x18];           // +0x6C = +0x60 (which is 0)
    *(uint8_t*)(this + 0x1f) = 0;      // +0x7C (byte)
    this[0x1e] = uVar3;                // +0x78
    this[0x21] = 0;                    // +0x84

    // Compute offset based on a self-referential pointer (likely from base class)
    if (this[0x12] == 0) {
        iVar4 = 0;
    }
    else {
        iVar4 = this[0x12] - 0x48;      // subtract 72 bytes
    }
    this[0x26] = iVar4;                // +0x98

    // Release any existing sub-objects pointed to by certain fields
    if (*piVar1 != 0) {
        FUN_004daf90(piVar1);           // likely destructor/release
        *piVar1 = 0;
    }
    if (*piVar2 != 0) {
        FUN_004daf90(piVar2);
        *piVar2 = 0;
    }
    if (this[0x30] != 0) {
        FUN_004daf90((int*)(this + 0x30));
        this[0x30] = 0;
    }

    this[0x2d] = DAT_00d65148;         // +0xB4
    this[0x23] = 0;                    // +0x8C
    this[0x24] = 0;                    // +0x90
    this[0x25] = 0;                    // +0x94

    // Second calculation using same offset (likely a member adjustment)
    if (this[0x12] != 0) {
        iVar5 = this[0x12] - 0x48;
    }
    this[0x36] = this[0x26] + 0x3c0;   // +0xD8 = +0x98 + 960
    this[0x35] = iVar5;                // +0xD4

    return this;
}