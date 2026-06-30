// FUNC_NAME: SomeEarsClass::constructorWithFlag
// Address: 0x00567f50
// Role: Constructor with a flag parameter (byte). Calls commonInit(), then conditionally calls cleanup() if flag bit 0 is set. Returns this pointer.
// FUN_00568000 is the common initialization routine (likely SomeEarsClass::commonInit).
// FUN_009c8eb0 is likely a cleanup/destructor (SomeEarsClass::cleanup).

undefined4 __thiscall SomeEarsClass::constructorWithFlag(byte param_2) {
    // Call the common initialization function (likely sets up vtable, initializes members)
    this->commonInit();

    // If param_2 bit 0 is set, perform cleanup (e.g., after a failed allocation or special init)
    if ((param_2 & 1) != 0) {
        this->cleanup(); // Possibly deallocates or reverts init
    }

    return this;
}