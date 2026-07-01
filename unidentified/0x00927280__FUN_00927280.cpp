// FUNC_NAME: SomeClass::constructor (likely EARS framework object with multiple base classes)
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte allocateFlag)
{
    // Set vtable pointers for the object (multiple inheritance)
    *this = &PTR_FUN_00d87980;           // Primary vtable
    this[4] = &PTR_LAB_00d87958;          // Secondary vtable at +0x10
    this[0x13] = &PTR_LAB_00d87948;       // Tertiary vtable at +0x4C
    this[0x16] = &PTR_LAB_00d87944;       // Quaternary vtable at +0x58

    // Call base class constructor (likely sets its own vtable)
    FUN_00927b50();

    // Override one of the vtable pointers after base construction
    this[0x16] = &PTR_LAB_00d87940;

    // Initialize global state (maybe singleton flag)
    DAT_01129a74 = 0;

    // Call additional initialization routines
    FUN_004083d0();
    FUN_005c16e0();

    // If allocated on heap, call a cleanup/destructor helper
    if ((allocateFlag & 1) != 0) {
        FUN_005c4480(this);
    }

    return this;
}