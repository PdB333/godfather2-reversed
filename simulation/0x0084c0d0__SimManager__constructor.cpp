// FUNC_NAME: SimManager::constructor
// Address: 0x0084c0d0
// This is the constructor for SimManager. It performs two-phase construction:
// first sets the base vtable, calls base constructor, then sets the derived vtable.
// The param_2 byte is a flag indicating if the object should be freed after construction.
// This is typical for EA EARS engine's allocation scheme.

undefined4* __thiscall SimManager::constructor(undefined4* this, byte allocFlag) {
    // Set base class vtable and RTTI
    *this = &PTR_FUN_00d74dd8;   // Base vtable pointer (+0x00)
    this[1] = &PTR_LAB_00d74dc8; // Base RTTI pointer (+0x04)

    // Initialize global critical section or reference counter for singleton
    FUN_004086d0(&DAT_0112dd08);  // Likely a mutex or reference count

    // Call the actual derived class construction logic (constructor body)
    FUN_0084bd40();  // Derived class initialization, sets up members

    // Another setup/cleanup (possibly base class destructor or post-init)
    FUN_004083d0();  // Likely initializes internal state

    // Switch vtable to derived class (vtable override)
    *this = &PTR_LAB_00d74db8;   // Derived vtable (+0x00)

    // Reset global manager flag to 0 (maybe busy flag or singleton indicator)
    DAT_0112ad5c = 0;  // +0x0112ad5c in .data

    // If allocFlag bit 0 is set, free the allocated memory (operator delete)
    if ((allocFlag & 1) != 0) {
        FUN_009c8eb0(this);  // operator delete(this)
    }

    return this;
}