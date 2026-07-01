// FUNC_NAME: UnknownClass::Constructor
// Reconstructed constructor for an unknown class (address 0x0082a240).
// Initializes vtable pointer and five member variables from global constants.
// Likely part of the game's static data initialization.

undefined4* __fastcall UnknownClass::Constructor(undefined4* this)
{
    // Call base class constructor (or some initialization routine)
    BaseClass::Constructor();  // FUN_008334a0

    // Global data used to initialize members
    undefined4 global1 = DAT_00e44630;
    undefined4 global2 = DAT_00d5ef88;
    undefined4 global3 = DAT_00d6471c;
    undefined4 global4 = _DAT_00d5cf70;

    // Set vtable pointer at offset 0x00
    *this = &vtable_00d7377c; // VTABLE

    // Member at +0x4C (offset 0x13 * 4)
    this[0x13] = global2; // DAT_00d5ef88

    // Member at +0x50 (offset 0x14 * 4)
    this[0x14] = global3; // DAT_00d6471c

    // Member at +0x54 (offset 0x15 * 4)
    this[0x15] = global4; // _DAT_00d5cf70 (overlapping?)

    // Member at +0x58 (offset 0x16 * 4)
    this[0x16] = global1; // DAT_00e44630

    // Member at +0x5C (offset 0x17 * 4)
    this[0x17] = global4; // _DAT_00d5cf70 again (reused)

    return this;
}