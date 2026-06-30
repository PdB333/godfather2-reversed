// FUNC_NAME: SomeClass::getFieldFromPtrAtOffset0x20
// Reconstructed getter: dereferences pointer at +0x20 then reads uint32 at +0xA4
uint32_t __thiscall SomeClass::getFieldFromPtrAtOffset0x20(void) const
{
    // Access pointer at this+0x20
    uint32_t* ptr = *(uint32_t**)((uint8_t*)this + 0x20);
    // Return value at ptr+0xA4
    return *(uint32_t*)((uint8_t*)ptr + 0xA4);
}