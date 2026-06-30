// FUNC_NAME: SomeClass::constructor
// Address: 0x0075fb20
// Role: Constructor for a class with a vtable at offset 0 and a subobject pointer at offset 0x18.
// Parameter param_2: flag byte; if bit 0 is set, deallocate this instance.

undefined4* __thiscall SomeClass::constructor(SomeClass* this, byte flags)
{
    // +0x00: vtable pointer
    this->vtable = &PTR_LAB_00d65334;

    // +0x18: pointer to a subobject (e.g., base class or embedded object)
    if (this->subObjectPtr != 0) {
        // Destroy the subobject at +0x18
        subObjectDestructor(this->subObjectPtr);
    }

    // Static initialization (e.g., engine singleton registration)
    BaseClassInit();

    // If the construction is not part of a pre-allocated pool, deallocate this instance
    if ((flags & 1) != 0) {
        operatorDelete(this);
    }

    return this;
}