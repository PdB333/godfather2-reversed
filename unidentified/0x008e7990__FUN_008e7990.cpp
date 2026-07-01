// FUNC_NAME: SomeClass::constructor
// Function address: 0x008e7990
// Role: Constructor for an EA EARS engine object. Calls base constructor and optionally allocates a 0x1b0-byte buffer.

undefined4 __thiscall SomeClass::constructor(SomeClass* this, byte param_2) {
    // Call base class constructor (likely initializing virtual base or common fields)
    this->baseConstructor(); // FUN_008e78e0

    // If the flag parameter has the lowest bit set, allocate a buffer of size 0x1b0 (432 bytes)
    // and store it (presumably in this at an offset). FUN_0043b960 is likely operator new or an allocation wrapper.
    if ((param_2 & 1) != 0) {
        this->allocateMember(0x1b0); // FUN_0043b960
    }

    return (undefined4)this;
}