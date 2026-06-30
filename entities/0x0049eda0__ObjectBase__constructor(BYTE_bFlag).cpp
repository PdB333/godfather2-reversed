// FUNC_NAME: ObjectBase::constructor(BYTE bFlag)
// Function address: 0x0049eda0
// Role: Constructor for a base object class. Calls internal init and optionally additional setup based on flag.

BYTE __thiscall ObjectBase::constructor(ObjectBase *this, BYTE bFlag)
{
    // Call internal initialization routine (likely sets up virtual table, zeroes fields, etc.)
    internalInit();

    // If the lowest bit of bFlag is set, call an additional initializer or allocator.
    if ((bFlag & 1) != 0)
    {
        // +0x00: likely a pointer to the object itself, passed to some manager or registry.
        additionalInit(this);  // FUN_009c8eb0
    }

    return this; // Return pointer to constructed object (standard for constructors)
}