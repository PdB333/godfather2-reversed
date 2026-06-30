// FUNC_NAME: EARSObject::constructor
// Function address: 0x00744100
// Role: Base constructor with optional finalization flag (bit0 of flags)
// Calls base constructor at 0x00743520, then if flags & 1, calls destructor/cleanup at 0x00624da0

// Forward declarations for callees
void __thiscall EARSObjectBase::constructor(void); // 0x00743520
void __thiscall EARSObjectBase::finalize(void);    // 0x00624da0 (possibly a destructor or cleanup)

// This function behaves as a constructor for EARSObject (or derived)
// param_1 (ecx) is the 'this' pointer
// param_2 is a byte flags: bit 0 indicates whether to call finalize after construction
void* __thiscall EARSObject::constructor(void* this, byte flags) {
    // Call base class initializer (likely zeroes fields, sets vtable, etc.)
    EARSObjectBase::constructor();
    
    // If bit 0 of 'flags' is set, perform additional finalization
    // This pattern is common in EARS for objects that can be constructed
    // with or without cleanup (e.g., placement new vs heap allocation)
    if ((flags & 1) != 0) {
        EARSObjectBase::finalize(); // note: finalize is called with same this pointer (ecx still set)
    }
    
    // Return constructed object pointer (standard constructor idiom)
    return this;
}