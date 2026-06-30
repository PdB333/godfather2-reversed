// FUNC_NAME: DerivedClass::DerivedClass
void __thiscall DerivedClass::DerivedClass(void)
{
    // +0x00: vtable pointer
    this->vtable = (void**)&PTR_FUN_00e32490; // Set vtable to base class
    BaseClass::BaseClass();                   // Call base constructor
    this->vtable = (void**)&PTR_LAB_00e30ea0; // Restore vtable to derived class
    return;
}