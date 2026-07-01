//FUNC_NAME: SomeClass::SomeClass
// Function address: 0x0083a060
// Role: Constructor for SomeClass. Calls base class constructor (0x00839de0). If flags bit 0 is set, calls additional initialization (0x009c8eb0).

SomeClass* __thiscall SomeClass::SomeClass(byte flags) {
    // Call base class constructor
    baseConstructor(); // FUN_00839de0

    // If the low bit of flags is set, perform extra initialization
    if ((flags & 1) != 0) {
        extraInit(); // FUN_009c8eb0(this)
    }

    return this;
}