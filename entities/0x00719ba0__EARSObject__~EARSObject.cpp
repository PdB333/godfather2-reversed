// FUNC_NAME: EARSObject::~EARSObject

// Destructor for EARSObject with memory management flag.
// param_2: bit 0 indicates whether to free heap memory (1 = free, 0 = skip)
// This follows the standard two-phase destruction pattern used by the engine.

EARSObject* __thiscall EARSObject::destructor(byte flag) {
    // Call base class destructor (likely EARSObjectBase::~EARSObjectBase)
    ::EARSObjectBaseDestructor();

    // If the low bit is set, free the object's memory via the engine allocator
    if ((flag & 1) != 0) {
        ::operatorDelete(this); // calls engine deallocation routine (FUN_009c8eb0)
    }

    // Return this pointer – some compilers return this from destructor
    return this;
}