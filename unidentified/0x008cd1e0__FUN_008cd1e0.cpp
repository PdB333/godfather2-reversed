// FUNC_NAME: SomeClass::~SomeClass
void __thiscall SomeClass::destructor(SomeClass *this)
{
    // Set vtable to derived class vtable (likely for virtual calls during destruction)
    this->vtable = &PTR_FUN_00d7c808;
    this->field_0xC = &PTR_LAB_00d7c7f4; // +0x0C

    // Release sub-object at offset +0x18
    releaseSubObject(this->m_pSubObject); // FUN_00943f10

    // Call virtual function from base subobject at +0x08
    // The base subobject has its own vtable; call function at vtable+4
    (*(code **)(*(int **)(this->field_0x08 + 8) + 4))();

    // Delete sub-object
    deleteSubObject(this->m_pSubObject); // FUN_00610100

    // Global cleanup
    globalCleanup(); // FUN_00485180

    // Unregister callback: function at 0x008cd1b0, type 2, userData = m_pSubObject, flag 0
    unregisterCallback(FUN_008cd1b0, 2, this->m_pSubObject, 0); // FUN_004851f0

    // Another cleanup
    finalCleanup(); // FUN_004083d0

    // Restore vtable to base class vtable (for base destructor)
    this->vtable = &PTR_LAB_00e2f638;
}