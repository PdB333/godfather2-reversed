// FUNC_NAME: SomeClass::SomeClass
void __thiscall SomeClass::SomeClass(void)
{
    // Initialize member fields at offsets +0x10 and +0x14 to zero
    this->field_10 = 0;  // +0x10: likely a pointer or integer
    this->field_14 = 0;  // +0x14: likely a pointer or integer

    // Call base class constructor or initialization routine
    BaseClass::BaseClass();  // 0x005c08f0
}