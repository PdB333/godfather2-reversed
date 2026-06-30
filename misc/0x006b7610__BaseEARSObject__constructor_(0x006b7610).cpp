// FUNC_NAME: BaseEARSObject::constructor (0x006b7610)
// Role: Initializes the vtable and two interface pointers (at offsets 0x3C and 0x48) for a base EARS engine object.
// Also calls sub-initialization functions: initGlobalData (FUN_004086d0) and initSubsystem (FUN_0046c640).

void __fastcall BaseEARSObject::constructor(BaseEARSObject *this)
{
    // Set primary vtable at offset 0
    this->vtable = (void **)&PTR_FUN_00d5e558;

    // Set secondary interface pointer at offset 0x3C (0xF * 4)
    this->interface1 = &PTR_LAB_00d5e548;

    // Set tertiary interface pointer at offset 0x48 (0x12 * 4)
    this->interface2 = &PTR_LAB_00d5e544;

    // Initialize global data or singleton (e.g., audio manager)
    // FUN_004086d0 likely calls a constructor for a static object
    FUN_004086d0(&DAT_0120e93c);

    // Initialize associated subsystem (e.g., sound system)
    FUN_0046c640();

    return;
}