// FUNC_NAME: SomeManager::constructor
SomeManager* __thiscall SomeManager::constructor(SomeManager* this, byte flags)
{
    // Set vtable pointers for multiple inheritance
    this->vtable1 = (void*)&PTR_FUN_00d85f70;      // +0x00: primary vtable
    this->vtable2 = (void*)&PTR_LAB_00d85f4c;      // +0x04: secondary vtable (base class 2)
    this->field_0x13 = (void*)&PTR_LAB_00d85f48;   // +0x13: tertiary vtable (base class 3) - first assignment
    // Note: immediately overwritten below – may be intentional or a bug
    this->field_0x13 = (void*)&PTR_LAB_00d85d80;   // +0x13: overwrite tertiary vtable

    // Reset global singleton flag
    DAT_0113005c = 0;

    // Call base initialization
    FUN_005c16e0();

    // If the low bit of flags is set, call a destructor or placement cleanup function
    if ((flags & 1) != 0)
    {
        FUN_005c4480(this);
    }

    return this;
}