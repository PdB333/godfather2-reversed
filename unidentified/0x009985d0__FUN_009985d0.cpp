// FUNC_NAME: SomeClass::constructor
// Function at 0x009985d0: Constructor for SomeClass, aligns with EA EARS engine pattern.
// Calls base initializer (FUN_009980f0) then optionally additional setup (FUN_009c8eb0) based on flag.

SomeClass* __thiscall SomeClass::constructor(SomeClass* this, byte flags)
{
    // Call base class constructor or common initialization routine
    this->baseConstructor();

    // If the lowest bit of 'flags' is set, perform extra initialization
    if ((flags & 1) != 0) {
        this->additionalSetup(this); // e.g., initFromMemory or allocate resources
    }

    return this;
}