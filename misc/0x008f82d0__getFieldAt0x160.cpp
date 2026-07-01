// FUNC_NAME: getFieldAt0x160
// Simplified getter that returns a value at offset 0x160 from the object.
// Likely returns a pointer or integer field (e.g., a component pointer, state value, or ID).
// In EA EARS engine, this offset often holds a reference to a sub-structure or a cached result.
// See caller at 0x00860e70 for usage context.

uint32_t __fastcall getFieldAt0x160(void* object)
{
    // Returns the value stored at offset 0x160 in the object's memory.
    return *(uint32_t*)((char*)object + 0x160);
}