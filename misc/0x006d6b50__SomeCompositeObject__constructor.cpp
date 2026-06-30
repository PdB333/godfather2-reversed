// FUNC_NAME: SomeCompositeObject::constructor
undefined4 * __thiscall SomeCompositeObject::constructor(undefined4 *this, undefined4 arg)
{
    // Call base class constructor
    BaseClass::BaseClass(arg);
    
    // Set main vtable pointer
    *this = &PTR_FUN_00d5f4d4;
    
    // Set interface vtable pointers at offsets +0x3C, +0x48, +0x50 (indices 0xF, 0x12, 0x14)
    this[0xf] = &PTR_LAB_00d5f4c4;
    this[0x12] = &PTR_LAB_00d5f4c0;
    this[0x14] = &PTR_LAB_00d5f4bc;
    
    // Zero out fields at offsets +0x58, +0x5C, +0x60, +0x64 (indices 0x16, 0x17, 0x18, 0x19)
    this[0x16] = 0;
    this[0x17] = 0;
    this[0x18] = 0;
    this[0x19] = 0;
    
    // Call another initialization routine
    SubClass::SecondPhaseInit();
    
    return this;
}