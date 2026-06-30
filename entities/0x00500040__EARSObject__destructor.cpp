//FUNC_NAME: EARSObject::destructor
undefined4 __thiscall EARSObject::destructor(undefined4 this, byte freeMemoryFlag)
{
    // Call base class destructor (or common cleanup)
    FUN_004ffdf0();
    
    // If the low bit of freeMemoryFlag is set, free the memory
    if ((freeMemoryFlag & 1) != 0) {
        FUN_009c8eb0(this); // deallocation function
    }
    
    return this;
}