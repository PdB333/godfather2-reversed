// FUNC_NAME: SomeClass::SomeClass
void __fastcall SomeClass::SomeClass(SomeClass* this)
{
    // Set vtable pointer to class's virtual function table
    // Address 0x00d61f1c is the vtable for SomeClass
    this->vtable = &someClass_vtable; // +0x00

    // Reset global instance count to zero (initial state)
    g_instanceCount = 0; // DAT_0112ad48
}