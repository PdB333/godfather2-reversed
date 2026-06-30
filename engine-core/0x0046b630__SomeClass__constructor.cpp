// FUNC_NAME: SomeClass::constructor
SomeClass * __thiscall SomeClass::constructor(SomeClass *this, byte flags) {
    // +0x00: vtable pointer
    this->vtable = &vtable_temp_0x00e3275c; // Temporary vtable for base initialization

    // Call base class constructor (likely initializes base members)
    this->baseConstructor(this);

    // Set final vtable for this class
    this->vtable = &vtable_final_0x00e30ea0;

    // If the low bit of flags indicates heap allocation, call cleanup/deallocator?
    // This pattern is unusual; it may be a guarded constructor or custom allocator.
    if ((flags & 1) != 0) {
        SomeClass::deallocateOrCleanup(this); // FUN_009c8eb0
    }

    return this;
}