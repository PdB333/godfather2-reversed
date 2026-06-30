// FUNC_NAME: BaseObject::constructor
void __thiscall BaseObject::constructor(BaseObject *this, uint param2, uint param3, ulong param4, ulong param5, ulong param6, ulong param7, uint param8, uint param9)
{
    // Dereference this to get internal data pointer (e.g., +0x00 is pointer to internal data block)
    InternalData *internalData = *(InternalData **)this;
    
    // Set vtable pointer at +0x14 in internal data to point to a new vtable (PTR_FUN_01123e04)
    **(uint ***)((uint)internalData + 0x14) = &PTR_FUN_01123e04;
    
    // Increment that pointer by 4 (skipping one vtable slot, likely for derived class adjustment)
    uint *vtablePtr = (uint *)((uint)internalData + 0x14);
    *vtablePtr += 4;
    
    // Call parent/base constructor with all parameters plus a flag (1)
    BaseClassConstructor(param2, param3, param4, param5, param6, param7, param8, param9, 1);
}