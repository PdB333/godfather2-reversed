// FUNC_NAME: SomeClass::constructor
// Function address: 0x00776070
// Role: Constructor for an EA EARS base class

void __thiscall SomeClass::constructor(SomeClass *this, byte allocFlags)
{
    // Set vtable pointer to the class-specific vtable
    this->vtable = &PTR_LAB_00d680e8;

    // Call base class constructor
    BaseClass::constructor(this); // FUN_004ac1e0

    // If the allocFlags indicate heap allocation, call destructor and free
    if ((allocFlags & 1) != 0) {
        SomeClass::destructorAndFree(this); // FUN_00624da0
    }
}