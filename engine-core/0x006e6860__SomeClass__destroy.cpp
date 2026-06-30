// FUNC_NAME: SomeClass::destroy
// Address: 0x006e6860
// Role: Destructor with optional memory deallocation. Calls internal destructor on first field (sub-object), then optionally frees the object memory.

// Callee: FUN_009c8f10 -> subObjectDestructor(uint32 subObjectPtr)
// Callee: FUN_009c8eb0 -> operatorDelete(void* ptr)

SomeClass* __thiscall SomeClass::destroy(SomeClass* this, byte flags)
{
    // Destroy the sub-object whose pointer is stored at offset 0x00 of this object
    subObjectDestructor(*(uint32*)this);

    // If bit 0 of flags is set, deallocate the memory for this object
    if (flags & 1)
    {
        operatorDelete(this);
    }

    return this;
}