// FUNC_NAME: UnknownClass::UnknownClass

// Function at 0x008ca8f0 - Constructor with optional allocation flag.
// Sets vtable, calls base constructor, and conditionally calls an initialization function.
// The param 'allocFlag' likely controls whether to free or perform additional setup.
undefined4 * __thiscall UnknownClass::UnknownClass(undefined4 *this, byte allocFlag) {
    *this = &PTR_FUN_00d7c050;                    // set vtable to derived class vtable
    FUN_004149b0();                                // base class constructor call (likely EARS base)
    if ((allocFlag & 1) != 0) {
        FUN_009c8eb0(this);                        // extra initialization or cleanup (e.g., heap-allocated path)
    }
    return this;
}