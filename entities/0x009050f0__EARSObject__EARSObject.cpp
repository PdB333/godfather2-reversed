// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x009050f0
// Role: Constructor for EARSObject with a flag indicating whether to call destroy after base initialization.
// This pattern is used in EA EARS engine for objects that may be allocated from a pool or heap.
// The flag's low bit (param_2 & 1) controls whether the object's destroy method is invoked immediately after construction,
// likely to handle cleanup of previously used memory in a pool scenario.

EARSObject* __thiscall EARSObject::EARSObject(byte flag) {
    // Call base class constructor (likely FrameworkObject or similar)
    FrameworkObject::FrameworkObject();

    // If the low bit of flag is set, call the destroy method on this object
    // This is unusual but may be used to reset or free the object after construction
    // in a pool recycling context.
    if (flag & 1) {
        this->destroy(); // or operator delete(this); depending on implementation
    }

    // Return the this pointer as per constructor convention
    return this;
}