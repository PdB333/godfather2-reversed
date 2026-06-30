// FUNC_NAME: SomeClass::constructor
// Function address: 0x006bd290
// Purpose: Constructor for SomeClass. Calls base constructor and optionally zero-initializes the object if flag bit 0 is set.

void __thiscall SomeClass::constructor(byte flags) {
    // Base class constructor (FUN_006bcd70)
    baseConstructor();
    
    // If bit 0 of flags is set, zero out memory at this pointer with size 0x80 (128 bytes)
    if (flags & 1) {
        memset(this, 0, 0x80);
    }
    
    // Returns this implicitly (this is returned by __thiscall)
}