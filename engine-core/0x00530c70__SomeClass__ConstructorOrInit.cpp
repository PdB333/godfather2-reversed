// FUNC_NAME: SomeClass::ConstructorOrInit
void __thiscall SomeClass::ConstructorOrInit(SomeClass* this)
{
    // Call base class or global initialization function
    FUN_00612e00(); // Possibly a base constructor or engine singleton initialization

    // Zero out member fields
    this->field_0x10 = 0; // +0x10: likely a 32-bit state or flag
    this->field_0x14 = 0; // +0x14: another 32-bit field (maybe paired with +0x10)
    this->field_0xa4 = 0; // +0xa4: a higher offset field, perhaps a pointer or handle
    this->field_0xa8 = 0; // +0xa8: consecutive field after +0xa4
}