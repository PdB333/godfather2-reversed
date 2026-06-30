// FUNC_NAME: EARSObject::EARSObject
// Address: 0x0046a240
// Constructor that sets vtable pointer and calls base class initializer (0x0043e2e0).
// The vtable pointer (0x00e32490) indicates this is a derived class constructor.
EARSObject * __thiscall EARSObject::EARSObject(EARSObject *this)
{
    // Set the vtable pointer for this class (derived from some base)
    this->vtable = (EARSObjectVTable *)&PTR_FUN_00e32490; // vtable at 0x00e32490

    // Call base class constructor (likely initializes common fields)
    FUN_0043e2e0(this); // base constructor at 0x0043e2e0

    return this;
}