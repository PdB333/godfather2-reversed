// FUNC_NAME: EARSObject::EARSObject
void __thiscall EARSObject::EARSObject(EARSObject *this)
{
    // Set vtable pointer to the class-specific vtable (0x00e326a8)
    this->vtable = (void**)&PTR_FUN_00e326a8;
    // Call base class constructor (EARSObjectBase or similar)
    FUN_0043e2e0(this); // base class initialization
}