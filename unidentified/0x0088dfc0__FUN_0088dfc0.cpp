// FUNC_NAME: SomeClass::constructor
SomeClass* __thiscall SomeClass::constructor(SomeClass* this, int someParam)
{
    // Call base class constructor (likely EARSObject or similar)
    BaseClass::constructor(someParam); // FUN_0046c590

    // Set primary vtable pointer
    this->vtable = &SomeClass_vtable; // PTR_FUN_00d77170

    // Set secondary vtable/interface pointers
    this->interfaceTable1 = &SomeClass_interface1; // +0x3C (PTR_LAB_00d77160)
    this->interfaceTable2 = &SomeClass_interface2; // +0x48 (PTR_LAB_00d7715c)

    // Initialize state fields to zero
    this->field_0x50 = 0; // +0x50
    *(short*)((int)this + 0x54) = 0; // +0x54 (short)
    *(short*)((int)this + 0x56) = 0; // +0x56 (short)
    this->field_0x58 = 0; // +0x58

    return this;
}