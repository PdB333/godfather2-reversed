// FUNC_NAME: SomeClass::~SomeClass
// Address: 0x0083cb70
// Role: Destructor for a class with two dynamically allocated members (at +0x10 and +0x18).
// Deallocates members, resets vtable, and conditionally deletes 'this'.

undefined4* __thiscall SomeClass::~SomeClass(undefined4* this, byte shouldDelete) {
    // Free member at offset +0x18 (param_1[6] in Ghidra)
    if (this[6] != 0) {
        deallocateMember(this + 6);  // FUN_004daf90 - likely operator delete or custom dealloc
    }
    // Free member at offset +0x10 (param_1[4])
    if (this[4] != 0) {
        deallocateMember(this + 4);
    }
    // Reset vtable pointer (class-specific global)
    *this = &PTR_LAB_00e2f0c0;
    // If deletion flag is set, call operator delete on this
    if ((shouldDelete & 1) != 0) {
        operatorDelete(this);  // FUN_009c8eb0
    }
    return this;
}