// FUNC_NAME: DerivedClass::~DerivedClass
void __thiscall DerivedClass::~DerivedClass(DerivedClass* this)
{
    // +0x00: vtable pointer
    // +0x5C: pointer to sub-object (e.g., allocated resource)
    // Set vtable to base class vtable before calling base destructor
    *(void**)this = (void*)&PTR_LAB_00d63f60; // BaseClass vtable

    // Release sub-object if it exists
    if (this->field_0x5C != nullptr)
    {
        cleanupSubObject(this->field_0x5C); // FUN_004daf90 - presumably deallocates/frees the sub-object
    }

    // Call base class destructor
    BaseClass::~BaseClass(); // FUN_004ac1e0
}