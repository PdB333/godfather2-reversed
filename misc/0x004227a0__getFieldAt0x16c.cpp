// FUNC_NAME: getFieldAt0x16c
uint32_t __fastcall getFieldAt0x16c(void* thisPtr)
{
    // Returns the value at offset 0x16c from the object base pointer.
    // Likely a pointer to a child object, a state flag, or a connection reference.
    return *(uint32_t*)((uint8_t*)thisPtr + 0x16c);
}