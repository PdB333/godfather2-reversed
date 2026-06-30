// Function at 0x00502170: Constructor for EARSObject (or derived class) with optional allocation flag
// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(EARSObject* this, byte allocFlag)
{
    // Call base class constructor (likely initializes common fields)
    baseConstructor();

    // If the low bit of allocFlag is set, perform additional initialization
    // (e.g., allocate memory, set up vtable, or register with manager)
    if ((allocFlag & 1) != 0) {
        additionalInit(this);
    }

    return this;
}