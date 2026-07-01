// FUNC_NAME: SomeGameObject::SomeGameObject
// Address: 0x00891050
// Role: Constructor for a derived game object with multiple interface vtables.
// Calls base class constructor at 0x0046c590 and initializes vtable pointers and data fields.

struct SomeGameObject {
    int* vtable;                 // +0x00: primary vtable
    // ... base class members (size up to +0x3C) ...
    int* secondaryVtable1;       // +0x3C: vtable for first secondary interface
    int* secondaryVtable2;       // +0x48: vtable for second secondary interface
    int field_0x50;              // +0x50
    short field_0x54;            // +0x54
    short field_0x56;            // +0x56
    int field_0x58;              // +0x58
};

SomeGameObject* __thiscall SomeGameObject::Constructor(SomeGameObject* this, int param2)
{
    // Call base class constructor (FUN_0046c590)
    BaseGameObject::BaseGameObject(param2);

    // Set primary vtable to class-specific vtable
    this->vtable = (int*)&PTR_FUN_00d7775c;

    // Set secondary vtable pointers for multiple inheritance
    this->secondaryVtable1 = (int*)&PTR_LAB_00d7774c;
    this->secondaryVtable2 = (int*)&PTR_LAB_00d77748;

    // Initialize data fields to zero
    this->field_0x50 = 0;
    *reinterpret_cast<short*>(this->secondaryVtable1 + 0x50) = 0; // offset 0x54
    *reinterpret_cast<short*>(reinterpret_cast<char*>(this) + 0x56) = 0; // offset 0x56
    this->field_0x58 = 0;

    return this;
}