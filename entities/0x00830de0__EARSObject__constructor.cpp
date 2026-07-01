// FUNC_NAME: EARSObject::constructor
// Address: 0x00830de0
// Constructor for EARSObject base class with dual vtable setup

void __fastcall EARSObject::constructor(undefined4 *this)
{
    // Set primary vtable pointer at offset 0x00
    *this = (undefined4 *)&PTR_FUN_00d737fc;   // +0x00: EARSObject vtable

    // Call base class constructor or initializer
    FUN_0082aea0(this);                        // likely ::EARSObjectBase::init

    // Set secondary vtable pointer at offset 0x30 (0xC * 4)
    this[0xc] = (undefined4 *)&PTR_LAB_00e32854; // +0x30: secondary interface vtable

    // Call secondary initializer
    FUN_00821f60(this);                        // likely ::SecondaryInterface::init
}