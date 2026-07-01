// FUNC_NAME: SomeClass::constructor
// Constructor for SomeClass (size 0x80 bytes). Sets vtable, initializes embedded objects,
// calls a global init function, and optionally deletes itself if the low bit of flags is set.
SomeClass* __thiscall SomeClass::constructor(SomeClass* this, byte flags) {
    // Set vtable pointer
    this->vtable = (void**)&PTR_FUN_00d7bee8;
    // Set function pointers at offsets +0x3C and +0x48
    this->field_3C = (void*)&PTR_LAB_00d7bed8;  // +0x3C
    this->field_48 = (void*)&PTR_LAB_00d7bed4;  // +0x48
    // Initialize sub-object at offset 0x54 (first constructor, then init)
    FUN_004086d0(&this->subobj1);  // sub-object constructor
    FUN_00408310(&this->subobj1);  // sub-object init
    // Initialize sub-objects at offsets 0x5C and 0x64 (only init)
    FUN_00408310(&this->subobj2);  // sub-object init
    FUN_00408310(&this->subobj3);  // sub-object init
    // Global initialization call
    FUN_0046c640();
    // If low bit set, delete this (size 0x80)
    if ((flags & 1) != 0) {
        FUN_0043b960(this, 0x80);
    }
    return this;
}