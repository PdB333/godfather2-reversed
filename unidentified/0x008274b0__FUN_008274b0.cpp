// FUNC_NAME: SomeGameObject::constructor
void __thiscall SomeGameObject::constructor(SomeGameObject *this)
{
    // Set main vtable pointer for this class
    this->vtable = (int *)&PTR_FUN_00d73570;          // +0x00: main vtable

    // Set secondary vtable pointers (multiple inheritance)
    this->field_0x3C = (int *)&PTR_LAB_00d73560;      // +0x3C: base class #1 vtable
    this->field_0x48 = (int *)&PTR_LAB_00d7355c;      // +0x48: base class #2 vtable

    // Conditionally call additional initialization
    if (g_SomeGlobalFlag != 0)                       // DAT_0112db84
    {
        SomeGameObject::additionalInit(this);        // FUN_00835410
    }

    // Common initialization for all instances
    CommonInitFunction();                             // FUN_0046c640
}