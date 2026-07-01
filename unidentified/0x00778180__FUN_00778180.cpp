// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x00778180
// Role: Constructor or init function with a flag that controls cleanup/delete.
// Calls base class initializer (FUN_007774b0) and if param_2 bit0 is set,
// calls a destroy/cleanup routine (FUN_00624da0) on the object.
// Returns the this pointer (common in decompiled constructors).

void __thiscall SomeClass::SomeClass(byte flags) {
    // Call base class constructor or initializer
    baseConstructor();  // Inferred: FUN_007774b0

    // If the lowest bit of flags is set, perform cleanup/delete
    if (flags & 1) {
        destroy();  // Inferred: FUN_00624da0(this)
    }

    // Note: The decompiled code returns param_1 (the this pointer),
    // but as a constructor this return is implicit.
}