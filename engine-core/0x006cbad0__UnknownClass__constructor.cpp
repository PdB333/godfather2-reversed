// FUNC_NAME: UnknownClass::constructor
undefined4* __thiscall UnknownClass::constructor(UnknownClass* this, undefined4 param)
{
    // Call base class constructor (FUN_0046c590) with the given parameter
    FUN_0046c590(param);
    
    // Set vtable pointer (offset 0x00)
    this->vtable = &PTR_FUN_00d5f100;
    
    // Set additional function/table pointers at offsets 0x3C (15*4) and 0x48 (18*4)
    this->field_0x3C = &PTR_LAB_00d5f0f0;
    this->field_0x48 = &PTR_LAB_00d5f0ec;
    
    return this;
}