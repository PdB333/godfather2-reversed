// FUNC_NAME: UnknownClass::constructor
undefined4* UnknownClass::constructor(undefined4* this, float scaleFactor, int sourceData)
{
    // Call base class constructor
    baseConstructor();
    
    // Initialize vtable pointer
    *this = &PTR_LAB_00d73448;  // vtable for UnknownClass
    
    // Set field at offset 0x4C (0x13 * 4) to sourceData->field_0x4C * scaleFactor
    this[0x13] = *(float*)(sourceData + 0x4C) * scaleFactor;  // +0x4C: some float field
    
    return this;
}