// FUNC_NAME: ManagedObject::~ManagedObject
void __thiscall ManagedObject::~ManagedObject(ManagedObject *this)
{
    // Set vtable to base class vtable (destruction guard)
    this->vtable = (void**)&PTR_FUN_00d5ef08;
    // Set overridden virtual function pointers to base implementations
    this->field_0x3C = (void*)&PTR_LAB_00d5eef8; // +0x3C
    this->field_0x48 = (void*)&PTR_LAB_00d5eef4; // +0x48
    this->field_0x50 = (void*)&PTR_LAB_00d5eef0; // +0x50

    // If internal sub-object exists (offset +0x90), release it
    if (this->field_0x90 != 0) {
        subObjectRelease((ManagedObject*)((char*)this + 0x90)); // FUN_004daf90
    }

    // Perform global cleanup (likely framework-level)
    globalCleanup(); // FUN_00473880
}