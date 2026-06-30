// FUNC_NAME: SomeClass::getFieldAt0x5c
// Function address: 0x006b18a0
// Role: Simple getter that reads a pointer (or integer) at offset +0x5c from the 'this' object.
// Used by multiple callers, likely to retrieve a stored object reference (e.g., an owner, target, or component).
uint32_t __thiscall SomeClass::getFieldAt0x5c() const
{
    // Read the 4-byte value at offset 0x5c in the class instance.
    return *(uint32_t*)((uint8_t*)this + 0x5c);
}