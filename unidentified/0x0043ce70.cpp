// FUN_0043ce70: EARSObject::EARSObject(byte flag)
EARSObject::EARSObject(byte flag) {
    // Initialize object (set vtable, zero fields) - calls FUN_0043ceb0
    init();

    // If flag bit 0 is set, perform additional memory allocation or registration
    if (flag & 1) {
        // May allocate a new backing buffer or register with manager - calls FUN_009c8eb0(this)
        allocateOrRegister();
    }
}