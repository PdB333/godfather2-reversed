// FUNC_NAME: SomeClass::Constructor
// Address: 0x00959aa0
// Role: Constructor for a class that initializes base and optionally derived components based on flag bit 0
int __thiscall SomeClass::Constructor(int this, byte flags) {
    // Call base class constructor (FUN_00959020)
    BaseClassConstructor(this);

    // If the lowest bit of 'flags' is set, perform additional initialization (FUN_005c4480)
    if ((flags & 1) != 0) {
        DerivedInit(this);
    }

    return this;
}