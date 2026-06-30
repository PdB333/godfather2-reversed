// FUNC_NAME: EARSObject::constructor
// Function address: 0x00620320
// EARS object base constructor with memory allocation flag.
// Calls common base initialization, then optionally additional init if param_2 & 1.

undefined4 __thiscall EARSObject::constructor(EARSObject* this, byte initFlags)
{
    // Call the base constructor or common initialization routine.
    FUN_00620350(this);

    // If the lowest bit is set, perform additional initialization
    // (e.g., allocate heap memory or set up virtual table).
    if ((initFlags & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}