// FUNC_NAME: EARSObject::EARSObject (constructor)
// Function address: 0x006a73a0
// Role: Constructs an EARSObject with an optional cleanup flag.

undefined4 __thiscall EARSObject::EARSObject(undefined4 this, byte constructorFlag)
{
    // Call base class initialization (sets up vtable, members, etc.)
    this->baseInit();

    // If the lowest bit of constructorFlag is set, free the object memory (size 0x78)
    if ((constructorFlag & 1) != 0)
    {
        // Deallocate the memory block for this object (size 0x78 = 120 bytes)
        operatorDelete(this, 0x78);
    }

    return this;
}