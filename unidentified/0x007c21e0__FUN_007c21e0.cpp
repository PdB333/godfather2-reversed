// FUNC_NAME: UnknownClass::constructor
undefined4 __thiscall UnknownClass::constructor(byte flags)
{
    // Call base class constructor (likely EARSObject or similar)
    UnknownClass::baseConstructor(); // FUN_007c2080

    // If flag bit 0 is set, perform additional cleanup/deallocation
    if ((flags & 1) != 0)
    {
        UnknownClass::conditionalCleanup(); // FUN_00624da0(this)
    }

    return (undefined4)this;
}