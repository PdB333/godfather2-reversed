// FUNC_NAME: setUInt32
// Function at 0x004b84c0: Simple setter that assigns an unsigned 32-bit value to the first member of an object.
// Likely a member function of a class that stores a single uint32 at offset 0x00.

void __thiscall setUInt32(void* this, uint32_t value)
{
    // Store the value into the object's first 4 bytes (offset 0x00)
    *(uint32_t*)this = value;
}