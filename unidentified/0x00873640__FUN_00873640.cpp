// FUNC_NAME: SomeClass::constructor
SomeClass* __thiscall SomeClass::constructor(SomeClass* this, byte allocFlag)
{
    // Set vtable pointer (offset +0x00)
    this->vtable = &PTR_LAB_00d76278;

    // Release sub-object at offset +0x60 (index 0x18)
    if (this->m_subObject != nullptr) {
        releaseSubObject(this->m_subObject); // FUN_004daf90
    }

    // Perform class-specific initialization
    initialize(); // FUN_0086aff0

    // If allocFlag bit 0 is set, deallocate this object
    if ((allocFlag & 1) != 0) {
        deallocate(this); // FUN_00624da0
    }

    return this;
}