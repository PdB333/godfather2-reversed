// FUNC_NAME: EARSObject::constructor
void * __fastcall EARSObject::constructor(EARSObject *this)
{
    // Set virtual function table pointer to class-specific vtable
    this->vtable = (void **)&PTR_FUN_00e32768;  // +0x00 vtable pointer

    // Call base class constructor or initialization routine
    FUN_0043e2e0(this);

    return this;
}