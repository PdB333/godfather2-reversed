// FUNC_NAME: SomeClass::SomeClass
// Address: 0x00901f50
// Constructor for class of size 0x70 bytes. Sets vtable, initializes base class pointers,
// constructs sub-object at offset 0x50, and calls a global initialization function.
// If param_2 (shouldFree) bit 0 is set, deallocates the object after construction (unusual).

SomeClass* __thiscall SomeClass::SomeClass(SomeClass* this, byte shouldFree)
{
    // Set vtable pointer
    *this = &PTR_FUN_00d81c20; // vtable for SomeClass
    // Set function pointers at offsets 0x3C and 0x48 (likely vtable pointers for base classes)
    this[0x0F] = &PTR_LAB_00d81c10; // offset 0x3C
    this[0x12] = &PTR_LAB_00d81c0c; // offset 0x48
    // Initialize sub-object at offset 0x50 (this + 0x14)
    FUN_004086d0(this + 0x14); // likely constructor for sub-object at offset 0x50
    FUN_00408310(this + 0x14); // another initialization
    FUN_00408310(this + 0x16); // offset 0x58
    // Global initialization function
    FUN_0046c640(); // probably a singleton or static init
    // If shouldFree bit is set, deallocate this object (size 0x70)
    if ((shouldFree & 1) != 0) {
        FUN_0043b960(this, 0x70); // operator delete or custom dealloc
    }
    return this;
}