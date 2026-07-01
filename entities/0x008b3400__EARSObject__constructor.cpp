// FUNC_NAME: EARSObject::constructor

EARSObject* __thiscall EARSObject::constructor(byte allocateFlag)
{
    // Set the primary virtual function table (vtable for the most derived class)
    this->vtable = &g_EARSObjectVtable;       // +0x00

    // Set secondary virtual function tables (for multiple inheritance)
    this->secondaryVtable1 = &g_SecondaryVtable; // +0x3C (offset 0xF * 4)
    this->secondaryVtable2 = &g_SecondaryVtable; // +0x48 (offset 0x12 * 4)

    // Call base class constructor (likely initializes common EARS object data)
    BaseClassConstructor();

    // If the low bit of allocateFlag is set, allocate memory for the object.
    // The size passed (0x5C = 92 bytes) matches the total size of this class.
    // This is typical for 'new' operations; when allocateFlag is 0, the memory
    // is assumed to be already allocated (placement new).
    if (allocateFlag & 1)
    {
        // Custom memory allocation (likely operator new or pool allocator)
        FUN_0043b960(this, 0x5C);
    }

    return this;
}