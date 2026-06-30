// FUNC_NAME: SomeGameObject::constructor
// Address: 0x00570d00
// Role: Object constructor with optional registration

SomeGameObject* __thiscall SomeGameObject::constructor(byte flags)
{
    // Call base class constructor (FUN_00581a70)
    baseConstructor();

    // If flags bit 0 is set, perform additional registration/initialization (FUN_009c8eb0)
    if (flags & 1) {
        registerObject();
    }

    return this;
}