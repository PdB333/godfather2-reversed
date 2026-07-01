// FUNC_NAME: SomeClass::SomeClass
// Address: 0x008359b0
// Constructor for SomeClass. Sets vtable to 0x00d73b40, calls base constructor, and optionally calls a cleanup function if flag bit 0 is set.

SomeClass* __thiscall SomeClass::SomeClass(SomeClass* this, byte flag)
{
    // Set vtable pointer (likely for SomeClass)
    this->vtable = (void*)0x00d73b40;

    // Call base class constructor (FUN_004149b0)
    baseConstructor(this);

    // If flag bit 0 is set, call cleanup/destructor function (FUN_009c8eb0)
    if ((flag & 1) != 0) {
        cleanupFunction(this);
    }

    return this;
}