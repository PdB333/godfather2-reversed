// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x008ddc30
// Role: Constructor with optional initialization based on flags
// Calls base constructor FUN_008dd9a0 and optionally calls FUN_009c8eb0 if bit 0 of flags is set.

int __thiscall SomeClass::SomeClass(byte flags) {
    // Call base class constructor
    baseConstructor(this);

    // If the low bit of flags is set, perform additional initialization
    if (flags & 1) {
        optionalInit(this);
    }

    return this;
}