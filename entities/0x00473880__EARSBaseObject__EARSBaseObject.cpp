// FUNC_NAME: EARSBaseObject::EARSBaseObject
void __fastcall EARSBaseObject::EARSBaseObject(EARSBaseObject* this)
{
    // Set vtable pointer at offset +0x00
    this->vtbl = &g_vtable_EARSBaseObject; // PTR_FUN_00e32af4

    // Initialize interface pointers at various offsets
    // +0x3C: pointer to some interface table (e.g., serialization)
    this->field_3C = &g_serializationVtbl; // PTR_LAB_00e32b18

    // +0x48: pointer to another interface
    this->field_48 = &g_eventHandlerVtbl; // PTR_LAB_00e32b28

    // +0x50: initially set to one pointer, then overridden
    this->field_50 = &g_propertyTableVtbl; // PTR_LAB_00e32b2c

    // Overwrite +0x50 with a different pointer (likely a bug or intentional override)
    this->field_50 = &g_networkReplicationVtbl; // PTR_LAB_00e32854

    // Call derived class initialization (e.g., constructor chaining)
    FUN_0046c640(); // EARSBaseObject::initDerived? or common init
}