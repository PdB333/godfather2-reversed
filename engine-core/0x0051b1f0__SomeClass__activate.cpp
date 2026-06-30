// FUNC_NAME: SomeClass::activate
// Address: 0x0051b1f0 - Sets a flag and performs initialization if not already done.
void SomeClass::activate() {
    // Check if the 0x40000 bit in flags at offset +0x0C is clear
    if ((this->flags & 0x40000) == 0) {
        // Set the flag to mark initialization
        this->flags |= 0x40000;
        // Call the initialization routine
        FUN_0051b120();
    }
}