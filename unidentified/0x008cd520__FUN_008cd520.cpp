// FUNC_NAME: BaseClass::constructor
undefined4 * __thiscall BaseClass::constructor(undefined4 *this, byte flags)
{
    int *allocPtr;
    
    // Set vtable pointer (global symbol at 0x00d7c8a8)
    *this = &PTR_FUN_00d7c8a8;
    
    // Call base class constructor (likely initializes common fields)
    FUN_008cd900();
    
    // If allocate flag (bit 0) is set, allocate memory via custom allocator
    if ((flags & 1) != 0) {
        // Get allocator function pointer (likely singleton)
        allocPtr = (int *)FUN_009c8f80();
        // Call placement new or constructor on allocated memory of size 0xC0
        (**(code **)(*allocPtr + 4))(this, 0xc0);
    }
    
    return this;
}