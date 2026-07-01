// FUNC_NAME: BaseGameObject::constructor
// Function at 0x009013f0 - Constructor for a base game object 
// (likely part of Entity hierarchy, initializes vtable pointers and sentinel magic numbers for debugging)
undefined4* __thiscall BaseGameObject::constructor(undefined4* this, undefined4 param_2)
{
    // Call base class constructor (likely EARS object base)
    FUN_0046c590(param_2);

    // Initialize multiple vtable/interface pointers
    // +0x54
    this[0x15] = 0;
    // +0x50: vtable for additional interface (overwritten later)
    this[0x14] = (undefined4*)&PTR_LAB_00d71d6c;
    // +0x00: primary vtable
    *this = (undefined4*)&PTR_FUN_00d8195c;
    // +0x3C: vtable for another interface
    this[0xf] = (undefined4*)&PTR_LAB_00d8194c;
    // +0x48: vtable for yet another interface
    this[0x12] = (undefined4*)&PTR_LAB_00d81948;
    // +0x50: override the earlier vtable entry
    this[0x14] = (undefined4*)&PTR_FUN_00d81940;

    // Zero out a series of fields (handles, counts, or pointers)
    this[0x16] = 0;                    // +0x58
    *(undefined2*)(this + 0x17) = 0;   // +0x5C (2 bytes)
    *(undefined2*)((int)this + 0x5E) = 0; // +0x5E (2 bytes)
    this[0x18] = 0;                    // +0x60
    *(undefined2*)(this + 0x19) = 0;   // +0x64 (2 bytes)
    *(undefined2*)((int)this + 0x66) = 0; // +0x66 (2 bytes)
    this[0x1a] = 0;                    // +0x68
    *(undefined2*)(this + 0x1b) = 0;   // +0x6C (2 bytes)
    *(undefined2*)((int)this + 0x6E) = 0; // +0x6E (2 bytes)

    // Store a global pointer (e.g., memory pool or list head)
    this[0x1c] = _DAT_00d5780c; // +0x70

    // Set a flag or initial count to 1
    this[0x1d] = 1; // +0x74

    // Mark the object with sentinel magic numbers for debugging/verification
    this[0x1e] = 0xbadbadba; // +0x78
    this[0x1f] = 0xbeefbeef; // +0x7C
    this[0x20] = 0xeac15a55; // +0x80
    this[0x21] = 0x91100911; // +0x84

    // Zero remaining fields (likely unused or reserved)
    this[0x22] = 0; // +0x88
    this[0x23] = 0; // +0x8C
    this[0x24] = 0; // +0x90
    this[0x25] = 0; // +0x94

    return this;
}