//FUNC_NAME: EARSObject::constructor
// Function address: 0x005d85e0
// Role: Constructor for a base EARS engine object. Takes a flag indicating whether to perform post-construction setup (e.g., registration with a manager).
// Calls base initialization (FUN_005d8600) and, if flag bit 0 is set, calls a post-construction function (FUN_009c8eb0).

undefined4 __thiscall EARSObject::constructor(EARSObject* this, byte initFlag)
{
    // Perform base class initialization (likely zeroing fields, setting vtable, etc.)
    this->baseInit();  // FUN_005d8600

    // If the low bit is set, run additional setup (e.g., register with object manager)
    if ((initFlag & 1) != 0) {
        this->postConstruct();  // FUN_009c8eb0
    }

    return this;
}