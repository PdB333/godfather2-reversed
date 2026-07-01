// FUNC_NAME: GodfatherGameManager::constructor
undefined4* __fastcall GodfatherGameManager::constructor(undefined4* this)
{
    // Call base class constructor (likely EARS::Framework::Object or similar)
    FUN_005bf9b0();

    // Set vtable pointer at +0x00
    *this = &PTR_FUN_00d8bed8;

    // Set secondary vtable/interface pointer at +0x10
    this[4] = &PTR_LAB_00d8beb0;

    // Set another pointer at +0x4C (first assignment, then overwritten)
    this[0x13] = &PTR_LAB_00d8bea8;

    // Store this in global singleton pointer
    DAT_01130594 = this;

    // Initialize fields at +0x50, +0x54, +0x58 to 0
    this[0x14] = 0;
    this[0x15] = 0;
    this[0x16] = 0;

    // Overwrite pointer at +0x4C with a different value
    this[0x13] = &PTR_LAB_00d8beac;

    // Initialize fields at +0x5C, +0x60, +0x64 to 0
    this[0x17] = 0;
    this[0x18] = 0;
    this[0x19] = 0;

    return this;
}