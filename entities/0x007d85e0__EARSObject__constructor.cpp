// FUNC_NAME: EARSObject::constructor
void* __thiscall EARSObject::constructor(EARSObject* this, byte allocFlag)
{
    // Set vtable pointer (address 0x00d6b95c)
    this->vtable = &g_vtable_EARSObject;
    
    // Call base class constructor
    FUN_0080ea60();  // likely EARSObject::baseConstructor(this)
    
    // If the low bit of allocFlag is set, deallocate memory (e.g., for exception-safe new)
    if (allocFlag & 1)
    {
        // Free the memory for this object
        FUN_00624da0(this);  // likely operator delete(this)
    }
    
    return this;
}