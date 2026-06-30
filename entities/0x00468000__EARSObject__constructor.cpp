// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(EARSObject* this)
{
    // +0x00: vtable pointer, initially set to derived class vtable (PTR_FUN_00e31f54)
    // +0x04: some pointer (likely a static data block or virtual base table)
    this->vtable = (void*)&PTR_FUN_00e31f54;
    this->field_04 = (void*)&PTR_LAB_00e31f60;

    // Call base class constructor (FUN_0043e380)
    baseClass_constructor(this);

    // After base construction, update to final vtable and pointer
    // +0x04: updated to &PTR_LAB_00e31f64
    this->field_04 = (void*)&PTR_LAB_00e31f64;
    this->vtable = (void*)&PTR_LAB_00e30ea0;

    // Global initialization flag reset
    DAT_01223470 = 0;
}