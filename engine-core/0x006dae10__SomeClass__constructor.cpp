// FUNC_NAME: SomeClass::constructor
// Address: 0x006dae10
// Reconstructed constructor for a class derived from multiple interfaces (multiple vtable pointers).
// Class size is 0xB8 bytes (184 bytes). The allocFlag indicates if memory needs freeing on failure.
undefined4 * __thiscall SomeClass::constructor(SomeClass *this, byte allocFlag)
{
    // Set vtable pointers for multiple inheritance / interfaces
    this->vfTable = &PTR_FUN_00e32b30;      // +0x00 primary vtable
    this->vfTable3C = &PTR_LAB_00e32b50;    // +0x3C second interface vtable
    this->vfTable48 = &PTR_LAB_00e32b60;    // +0x48 third interface vtable
    this->vfTable50 = &PTR_LAB_00e32854;    // +0x50 fourth interface vtable (overwrites previous assignment to same offset)
    // Call base class constructor (likely Entity or Node initialization)
    FUN_0046c640();
    // If allocFlag bit 0 is set, free this memory (0xB8 bytes) – typical placement delete
    if ((allocFlag & 1) != 0) {
        FUN_0043b960(this, 0xb8);
    }
    return this;
}