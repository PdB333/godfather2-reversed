// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x006f7680
// Role: Constructor for a derived class, calls base constructor with vtable pointer,
// then initializes own members.

void __thiscall SomeClass::SomeClass(SomeClass* this)
{
    // Call base class constructor, passing the vtable pointer from static data
    // BaseClass::BaseClass sets the vtable pointer at offset 0x00
    BaseClass::BaseClass(this, (int*)&s_vtable_006f7670);
    // Initialize derived class specific members
    InitializeMembers(this);
}