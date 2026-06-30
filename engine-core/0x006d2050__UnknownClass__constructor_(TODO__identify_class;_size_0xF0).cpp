// FUNC_NAME: UnknownClass::constructor (TODO: identify class; size 0xF0)
// Address: 0x006D2050
// Role: Constructor with allocation flag. Base constructor called first; if bit0 of flags is set, calls a member at vtable offset 0x4 (likely deallocation) with size 0xF0.

undefined4 __thiscall UnknownClass::constructor(UnknownClass* this, byte flags)
{
    int* pVtable;

    // Call base class constructor (likely EARSObject or similar)
    UnknownClass::BaseConstructor(this);  // FUN_006d1bc0

    // If the allocation flag (bit 0) is set, perform additional setup
    if ((flags & 1) != 0)
    {
        // Get the vtable pointer for this class (or allocator interface)
        pVtable = (int*)UnknownClass::getAllocatorVtable();  // FUN_009c8f80

        // Call the function at vtable[1] (offset 4) with parameters (this, 0xF0)
        // This is likely an operator delete or deallocation routine for objects of size 0xF0.
        ((void (__thiscall*)(UnknownClass*, unsigned int))(*pVtable + 4))(this, 0xF0);
    }

    return (undefined4)this;
}