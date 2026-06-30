// FUNC_NAME: SomeClass::Construct (0x0067d800)
// Constructor with optional allocation/deallocation flag.
// param_2 bit 0: if set, calls cleanup function (likely for heap-allocated objects).
SomeClass* __thiscall SomeClass::Construct(SomeClass* thisPtr, byte shouldCleanup) {
    // Set vtable pointer to the class's vtable (0x00d57f30)
    thisPtr->vtable = &SomeClass_vtable;
    // Call base class constructor (likely common initialization)
    BaseClass::Construct(thisPtr); // FUN_004149b0
    // If bit 0 is set, call cleanup function (e.g., destructor or placement delete)
    if (shouldCleanup & 1) {
        SomeClass::Deallocate(thisPtr); // FUN_009c8eb0
    }
    return thisPtr;
}