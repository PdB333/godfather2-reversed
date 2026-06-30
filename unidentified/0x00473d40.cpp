// FUNC_00473D40: SomeClass::constructor
// This function appears to be a constructor that initializes an object with vtable pointers and calls a base constructor.
// It optionally performs memory allocation if param_2 has bit 0 set, using a global allocation function.
// Offsets:
//   +0x00: vtable pointer (base class)
//   +0x3C: pointer to another vtable or callback table
//   +0x48: pointer to another vtable or callback table
//   +0x50: pointer to a static label (overwritten later)

undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte allocFlag)
{
    // Set up vtable pointers
    *this = &PTR_FUN_00e32b30;     // +0x00: base vtable
    this[0xf] = &PTR_LAB_00e32b50; // +0x3C: secondary vtable or callback
    this[0x12] = &PTR_LAB_00e32b60; // +0x48: another callback
    this[0x14] = &PTR_LAB_00e32b64; // +0x50: initial callback (overwritten below)
    this[0x14] = &PTR_LAB_00e32854; // +0x50: final callback (overwrites previous)

    // Call base class constructor
    FUN_0046c640();

    // If bit 0 of allocFlag is set, allocate memory via a global function
    if ((allocFlag & 1) != 0)
    {
        // Call a virtual function from a global object at DAT_01223410 + 0x2D4
        // (similar to a placement new or custom allocator)
        (*(code **)(**(int **)(DAT_01223410 + 0x2d4) + 4))(this, 0);
    }

    return this;
}