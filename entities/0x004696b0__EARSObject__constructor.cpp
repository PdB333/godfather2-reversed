// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(EARSObject* this) // param_1 == this
{
    // Initialize vtable pointers: typical pattern for multiple inheritance
    // Set primary vtable to base class vtable (PTR_FUN_00e320ac)
    this->vtable0 = &PTR_FUN_00e320ac; // +0x00: first vtable pointer
    // Set secondary vtable to base class vtable block (PTR_LAB_00e320b8)
    this->vtable1 = &PTR_LAB_00e320b8; // +0x04: second vtable pointer

    // Call base class constructor (likely initializes base parts)
    FUN_0043e380(this); // base class constructor / init

    // Adjust vtable pointers to derived class vtables after base init
    this->vtable1 = &PTR_LAB_00e320bc; // +0x04: updated secondary vtable
    this->vtable0 = &PTR_LAB_00e30ea0; // +0x00: updated primary vtable

    // Global flag: possibly singleton or initialization flag
    g_bSomeGlobalFlag = 0; // _DAT_01223478 set to 0
}