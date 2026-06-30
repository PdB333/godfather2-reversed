// FUNC_NAME: getFieldAtOffset4
uint32_t __fastcall getFieldAtOffset4(void* thisPtr)
{
    // Returns the 32-bit value stored at offset +0x4 from the object's base address.
    return *(uint32_t*)((uintptr_t)thisPtr + 4);
}