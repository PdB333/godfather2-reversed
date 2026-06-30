// FUNC_NAME: getFieldAt0x6c
uint32_t __fastcall getFieldAt0x6c(void* thisPtr)
{
    // Return the 4-byte value stored at offset 0x6c in the object.
    // This is a simple accessor for a field at that offset.
    return *(uint32_t*)((uint8_t*)thisPtr + 0x6c);
}