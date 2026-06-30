// FUNC_NAME: EARSObject::EARSObject
undefined4* __thiscall EARSObject::EARSObject(undefined4* this, byte allocFlag) {
    // Set vtable pointer (base class)
    this[0] = &PTR_FUN_00e32e48;                // +0x00: vtable
    // Initialize additional method table pointers
    this[0xf] = &PTR_LAB_00e32e64;              // +0x3C: method table #2
    this[0x12] = &PTR_LAB_00e32e74;             // +0x48: method table #3

    // Construct and initialize sub-object at offset 0x14 (4*5)
    // FUN_004086d0 - sub-object constructor
    FUN_004086d0(this + 0x14);                 // calls constructor on sub-object
    // FUN_00408310 - sub-object initialization
    FUN_00408310(this + 0x14);                 // initializes sub-object after construction

    // Global initialization (likely singleton or engine state)
    FUN_0046c640();                            // sets up some global state

    // Optional cleanup if this object was dynamically allocated
    if ((allocFlag & 1) != 0) {
        // Call destructor via thunk from global manager
        // DAT_01223410 + 0x2d4 points to a structure containing a function pointer at offset 4
        (**(code **)(**(int **)(DAT_01223410 + 0x2d4) + 4))(this, 0);
    }

    return this;
}