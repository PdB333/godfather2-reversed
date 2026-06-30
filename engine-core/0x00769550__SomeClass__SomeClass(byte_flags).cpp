// FUNC_NAME: SomeClass::SomeClass(byte flags)
// Address: 0x00769550
// Identified as a constructor for a class derived from a base class (base constructor at 0x00768f10).
// The flags parameter controls additional initialization: if bit 0 is set, calls an extra setup function.

void SomeClass::SomeClass(byte flags) {
    // Call base class constructor/initializer
    initializeBase();  // FUN_00768f10
    // If the low bit is set, perform extra initialization
    if ((flags & 1) != 0) {
        setupDerived();  // FUN_00624da0
    }
}