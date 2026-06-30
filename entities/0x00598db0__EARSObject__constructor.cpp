// FUNC_NAME: EARSObject::constructor
// Function address: 0x598db0 - Constructor: sets vtable pointer
// This is a base class constructor that initializes the vtable to the class-specific table.
void __thiscall EARSObject::constructor(EARSObject *this)
{
    // +0x00: vtable pointer (points to PTR_LAB_00e3b030)
    this->vtable = (void***)&PTR_LAB_00e3b030; // set vtable to class-specific table
}