// FUNC_NAME: SomeClass::constructor

// Constructor for a class from the EARS engine.
// Calls a base class initializer, then conditionally calls a cleanup function if a flag bit is set.
// param_2: flags byte (bit 0 triggers a secondary operation, likely a destructor or deallocation)
// returns this pointer

SomeClass* __thiscall SomeClass::constructor(SomeClass* this, byte flags)
{
    // Call base class constructor (likely a shared initialization routine)
    // FUN_0054a180 - assumed to be a base class constructor or initializer
    this->baseInit();

    // If the lowest bit of flags is set, call a function that may perform cleanup or deallocation.
    // This pattern is common in EA's EARS engine for objects that can be stack or heap allocated.
    // FUN_009c8eb0 - likely a destructor-like function that frees resources or memory
    if ((flags & 1) != 0)
    {
        this->cleanup();  // FUN_009c8eb0
    }

    return this;
}