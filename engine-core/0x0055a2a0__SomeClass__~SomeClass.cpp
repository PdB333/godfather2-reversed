// FUNC_NAME: SomeClass::~SomeClass
// Destructor at 0x0055a2a0 - cleans up internal state and sets vtable to purecall guard
void __thiscall SomeClass::~SomeClass(SomeClass* this)
{
    // Set vtable to current class (active during destruction)
    this->vtable = (void**)&PTR_FUN_00e3a038;
    this->secondaryVtable = (void**)&PTR_LAB_00e3a054;

    // If a member at offset +0x34 is non-null, perform cleanup
    if (this->field_0x34 != 0) {
        FUN_009f1b20(this);   // Cleanup function 1
        FUN_009f01a0();       // Cleanup function 2 (no parameter)
    }

    // After cleanup, replace vtable with base class or purecall guard
    this->secondaryVtable = (void**)&PTR_LAB_00dc3dd4;
    this->vtable = (void**)&PTR___purecall_00e3924c;
    return;
}