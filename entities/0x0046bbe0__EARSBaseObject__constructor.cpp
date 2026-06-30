// FUNC_NAME: EARSBaseObject::constructor
// Address: 0x0046bbe0 - Constructor for base EARS object. Sets vtable and calls base initializer.

void* __thiscall EARSBaseObject::constructor(void* this) {
    // +0x00: vtable pointer - set to class-specific vtable
    *(int*)this = (int)&PTR_FUN_00e327c0; // vtable for EARSBaseObject (global symbol)
    // Call base class initialization (likely zeroes members, sets up ref counting, etc.)
    FUN_0043e2e0(this);
    return this;
}