// FUNC_NAME: BaseObject::BaseObject
// Function at 0x008ca8c0: Constructor for a base class (likely EA engine base object)
// Initializes vtable and calls base constructor for common initialization.

BaseObject * __thiscall BaseObject::BaseObject(BaseObject *this, int someId, int someFlags)
{
    // Call base class constructor (FUN_00414970) with provided parameters
    FUN_00414970(someId, someFlags);
    // Set vtable pointer (first field at offset 0x00)
    this->vtable = (int *)&PTR_FUN_00d7c050;
    return this;
}