// FUNC_NAME: SomeClass::SomeClass
// Address: 0x007dd7a0
// Constructor for SomeClass. param_2 is a flag (bit 0 indicates whether to call cleanup?).
SomeClass* __thiscall SomeClass::SomeClass(SomeClass* this, byte flag) {
    // Set vtable pointer to class's vtable
    *this = &PTR_LAB_00d6b95c; // vtable for SomeClass
    // Call base class constructor or initialization routine
    FUN_0080ea60(); // likely base constructor
    // If flag bit 0 is set, call a cleanup/destructor function (unusual in constructor)
    if ((flag & 1) != 0) {
        FUN_00624da0(this); // possibly operator delete or destructor
    }
    return this;
}