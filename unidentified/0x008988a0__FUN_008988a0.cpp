// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x008988a0
// This constructor initializes a class of size ~100 bytes. It sets three vtable/interface pointers,
// initializes two sub-objects at offsets +0x50 (0x14*4) and +0x58 (0x16*4), calls a global init,
// and conditionally frees memory if the flags parameter (param_2) has bit 0 set.
// The conditional delete suggests this may be part of a factory pattern where the constructor
// is called on pre-allocated memory and the flag indicates whether to also release it.

SomeClass* __thiscall SomeClass::SomeClass(byte flags)
{
    // Set primary vtable pointer at offset +0x00
    this->vtable = &PTR_FUN_00d77ca0;

    // Set first interface vtable at offset +0x3C (0xF * 4)
    this->interfaceVtable1 = &PTR_LAB_00d77c90;

    // Set second interface vtable at offset +0x48 (0x12 * 4)
    this->interfaceVtable2 = &PTR_LAB_00d77c8c;

    // Initialize sub-object at offset +0x50 (this + 0x14) with two calls
    subObjectInit1(this + 0x14);    // First initialization function (FUN_004086d0)
    subObjectInit2(this + 0x14);    // Second initialization function (FUN_00408310)

    // Initialize sub-object at offset +0x58 (this + 0x16) with one call
    subObjectInit2(this + 0x16);    // FUN_00408310

    // Global initialization routine (FUN_0046c640)
    globalInitFunction();

    // If the object was dynamically allocated (flags & 1), free its memory
    if (flags & 1) {
        operatorDelete(this, 100);  // Deallocation function (FUN_0043b960, size likely 0x64)
    }

    return this;
}