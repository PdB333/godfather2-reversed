// FUNC_NAME: SomeClass::getFieldAtOffset4
uint32_t __fastcall SomeClass::getFieldAtOffset4(int thisPtr)
{
    // Returns the 32-bit value stored at offset +0x04 from the object's base
    return *(uint32_t *)(thisPtr + 4);
}