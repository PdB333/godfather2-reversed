// FUN_00424bc0: EARSObject::EARSObject
// Function address: 0x00424bc0
// Role: Constructor for EARSObject, with an initialization flag.
// Unconditionally calls base class constructor (at 0x424c10).
// If the low bit of `flag` is set, a cleanup/destructor-like call is made (at 0x9c8eb0).

EARSObject* __thiscall EARSObject::EARSObject(byte flag)
{
    // Call base class constructor (likely initializes allocation or vtable)
    this->baseConstructor(); // FUN_00424c10

    // If bit 0 of flag is set, invoke a cleanup or destructor function.
    // This pattern is unusual for a standard constructor; possibly used for
    // reinitialization or conditional resource handling.
    if ((flag & 1) != 0) {
        this->cleanup(); // FUN_009c8eb0
    }

    return this;
}