// FUNC_NAME: BaseObject::constructor
BaseObject * __fastcall BaseObject::constructor(BaseObject *this)
{
    // Call base class constructor (likely EARS::Framework::Object or similar)
    FUN_007aaaa0();

    // Set vtable pointer to class-specific vtable
    this->vtable = (void *)&PTR_LAB_00d6ef38; // +0x00

    // Initialize member at offset 8 to 0 (e.g., pointer, flag, or reference count)
    this->field_8 = 0; // +0x08

    return this;
}