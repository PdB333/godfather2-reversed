// FUNC_NAME: SomeClass::~SomeClass
void __fastcall SomeClass::~SomeClass(SomeClass* this)
{
    // Set vtable to destructor vtable (likely for base class destruction)
    this->vtable = &PTR_FUN_00e3e78c; // +0x00: vtable pointer (destructor stage)
    
    // Call base class destructor or common cleanup routine
    baseClassDestructor(); // FUN_005c0360
    
    // Clear fields (possibly flags or pointers)
    this->field_0x0c = 0; // param_1[3]
    this->field_0x08 = 0; // param_1[2]
    
    // Release owned child object if it exists
    if (this->m_childObject != 0) { // param_1[1]
        // Call virtual release/delete on child object (e.g., through some manager)
        (**(code**)(**(int**)(DAT_012234ec + 4) + 4))(this->m_childObject, 0);
    }
    this->m_childObject = 0;
    
    // Restore vtable to non-destructor vtable (or final vtable)
    this->vtable = &PTR_LAB_00e3e74c; // +0x00: vtable pointer (final)
    
    return;
}