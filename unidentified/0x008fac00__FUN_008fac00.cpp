// FUNC_NAME: SomeClass::Constructor
// Address: 0x008fac00
// Role: Constructor for a game object, initializes base class and optionally allocates memory of size 0x4F4.

undefined4 __thiscall SomeClass::Constructor(SomeClass* this, byte flags)
{
    // Call base class constructor (likely initializes common fields)
    baseConstructor();

    // If bit 0 of flags is set, allocate memory for internal buffer (size 0x4F4 bytes)
    if ((flags & 1) != 0) {
        allocateMemory(this, 0x4F4); // +0x4F4 is the size of the allocated block
    }

    return this;
}