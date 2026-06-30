// FUNC_NAME: FUN_0070c4d0: SomeEngineObject::constructor
// Function address: 0x0070c4d0
// Role: Constructor for an engine object with optional internal allocation.
// Behavior: Calls base class initializer, then if flags bit 0 is set,
// allocates an internal buffer/object of size 0x3b0 (944 bytes).

SomeEngineObject* __thiscall SomeEngineObject::constructor(SomeEngineObject* this, byte flags)
{
    // Call the base class constructor (likely common initialization)
    // Original: FUN_0070be60
    BaseClass::constructor(this);

    // If the lowest bit of 'flags' is set, allocate additional memory
    // (potentially for internal data, vtable, or a subobject).
    // Original: FUN_0043b960(this, 0x3b0)
    if (flags & 1) {
        allocateInternalMemory(this, 0x3b0);
    }

    return this;
}