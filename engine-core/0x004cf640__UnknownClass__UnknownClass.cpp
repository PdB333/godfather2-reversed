// FUNC_NAME: UnknownClass::UnknownClass
void UnknownClass::UnknownClass()
{
    int *pPointer;
    
    // Call base class constructor
    BaseClass::BaseClass(this);
    
    // Set primary vtable pointer at offset 0x00
    this->vtable = &VTable_00e36c80;
    
    // Set secondary vtable pointers for interfaces or base classes
    this->vtable2 = &VTable_00e36ca0;    // +0x3C
    this->vtable3 = &VTable_00e36cb0;    // +0x48
    
    // Initialize various member fields to zero
    this->field_0x50 = 0;                // +0x50
    *(short *)&this->field_0x54 = 0;     // +0x54 (word)
    *(short *)&this->field_0x56 = 0;     // +0x56 (word)
    this->field_0x58 = 0;                // +0x58
    *(short *)&this->field_0x5C = 0;     // +0x5C (word)
    *(short *)&this->field_0x5E = 0;     // +0x5E (word)
    
    this->field_0x80 = 0;                // +0x80
    this->field_0x84 = 0;                // +0x84
    *(char *)&this->field_0x8C = 0;      // +0x8C (byte)
    this->field_0x88 = -1;               // +0x88
    
    // Save pointer to field at +0x80 for cleanup
    pPointer = &this->field_0x80;
    
    // Zero out a block of 8 words starting at +0x60
    this->field_0x60 = 0;                // +0x60
    this->field_0x64 = 0;                // +0x64
    this->field_0x68 = 0;                // +0x68
    this->field_0x6C = 0;                // +0x6C
    this->field_0x70 = 0;                // +0x70
    this->field_0x74 = 0;                // +0x74
    this->field_0x78 = 0;                // +0x78
    this->field_0x7C = 0;                // +0x7C
    
    // Release any existing object pointed to by field_0x80
    if (*pPointer != 0) {
        SomeReleaseFunction(pPointer);
        *pPointer = 0;
    }
}