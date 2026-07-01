// FUNC_NAME: SomeGameObject::SomeGameObject
// Address: 0x009552e0
// Role: Constructor for a game object class. Initializes vtable and calls base class constructors.

void __thiscall SomeGameObject::SomeGameObject(SomeGameObject* this)
{
    // Set vtable pointer at offset 0x00
    this->vtable = (void**)&PTR_FUN_00d8c0b4;

    // Set function pointers at offsets 0x3C, 0x48, 0x50 (indices 0xF, 0x12, 0x14)
    // These are likely virtual method overrides or additional function tables.
    this->field_0x3C = (void*)&PTR_LAB_00d8c0a4;   // +0x3C
    this->field_0x48 = (void*)&PTR_LAB_00d8c0a0;   // +0x48
    this->field_0x50 = (void*)&PTR_LAB_00d8c09c;   // +0x50

    // Call base class constructor or initialization function with argument 0
    FUN_00976360(0);

    // Call another initialization function
    FUN_00473880();
}