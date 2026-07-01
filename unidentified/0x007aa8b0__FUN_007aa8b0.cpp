//FUNC_NAME: SomeClass::SomeClass
// Address: 0x007aa8b0
// Role: Constructor for SomeClass with optional cleanup flag (bit 0 of param_2)

SomeClass* __thiscall SomeClass::SomeClass(SomeClass* this, byte flag)
{
    // Set vtable pointer (PTR_LAB_00d6b95c)
    this->vtable = (void*)&SomeClass_vtable;

    // Call base class constructor (FUN_0080ea60)
    BaseClass::BaseClass(this);

    // If bit 0 of flag is set, perform cleanup/destruction (FUN_00624da0)
    if (flag & 1)
    {
        SomeClass::cleanup(this);
    }

    return this;
}