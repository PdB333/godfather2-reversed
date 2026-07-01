// FUNC_NAME: UnknownClass::ConstructorWithFlag
// Address: 0x00879140
// Reconstructed from __thiscall, returns this pointer
// param_2 (byte) bit 0 controls additional initialization (likely copy or clone flag)

__thiscall UnknownClass::ConstructorWithFlag(byte isCopy) {
    // Call base class or common initialization routine (static? no this?)
    CommonInit(); // FUN_00874970

    if ((isCopy & 1) != 0) {
        // Perform specific initialization if copy mode is specified
        SpecificInit(); // FUN_009c8eb0(this)
    }

    return this;
}