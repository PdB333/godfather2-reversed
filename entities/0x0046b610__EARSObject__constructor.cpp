// FUNC_NAME: EARSObject::constructor
// Address: 0x0046b610
// Role: Constructor that initializes vtable (base at +0x00) and calls base class initializer.

EARSObject* __thiscall EARSObject::constructor(EARSObject* this_)
{
    // Initialize virtual function table pointer (offset +0x00)
    this_->vtable = &PTR_FUN_00e3275c;

    // Call base class constructor / initializer
    FUN_0043e2e0(this_);

    return this_;
}