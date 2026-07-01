// FUN_NAME: SomeClass::ctor
// Address: 0x009768b0
// Role: Constructor for SomeClass with conditional additional initialization.
// param_2: flags - bit 0 triggers an extra initialization step (e.g. registration, pool allocation).
uint32 SomeClass::ctor(uint8 flags) {
    // Base initialization (likely base class constructor or common setup)
    this->initBase();                         // FUN_004ec190

    // Conditional secondary initialization
    if (flags & 1) {
        this->initExtra();                     // FUN_004eb3d0
    }

    return this;                               // Return the constructed object
}