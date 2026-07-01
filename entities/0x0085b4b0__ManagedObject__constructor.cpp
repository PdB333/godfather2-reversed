// FUNC_NAME: ManagedObject::constructor
// Address: 0x0085b4b0
// Constructor that initializes the object and optionally releases prior resources.
// flags: bit 0 – if set, calls cleanup after base initialization.

ManagedObject* __thiscall ManagedObject::constructor(byte flags)
{
    // Call base initialization (0x0085ad20 – likely sets vtable/zeroes memory)
    baseInit();

    // If bit 0 is set, call external cleanup function (0x009c8eb0)
    if (flags & 1)
    {
        cleanupResource(this);
    }

    return this;
}