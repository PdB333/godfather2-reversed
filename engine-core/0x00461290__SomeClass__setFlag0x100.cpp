// FUNC_NAME: SomeClass::setFlag0x100
void __fastcall SomeClass::setFlag0x100(void* thisPtr)
{
    // Set bit 8 (0x100) at offset +0x184 (likely flags field)
    *(uint32_t*)((uint8_t*)thisPtr + 0x184) |= 0x100;
}