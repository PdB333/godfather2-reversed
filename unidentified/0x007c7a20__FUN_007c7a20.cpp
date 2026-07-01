// FUNC_NAME: SomeClass::~SomeClass
void __fastcall SomeClass::~SomeClass(SomeClass* this)
{
    // Set vtable to this class's vtable for proper virtual dispatch during destruction
    this->vtable = (void**)&PTR_FUN_00d6e930; // +0x00: vtable pointer for this class

    // If the member pointer at offset +0x08 is non-null, delete it
    if (this->m_pSomeMember != (void*)0) { // +0x08: pointer to dynamically allocated member
        // Safely delete the member object and nullify the pointer
        deleteMember(&this->m_pSomeMember);
    }

    // Reset vtable to base class vtable so subsequent base destructor runs correctly
    this->vtable = (void**)&PTR_LAB_00d6ba68; // +0x00: vtable pointer for base class
    return;
}