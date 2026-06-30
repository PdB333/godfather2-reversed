// FUNC_NAME: copyStructure
void __fastcall copyStructure(void* dest, void* src)
{
    // Copy first 12 dwords (48 bytes)
    for (int i = 0; i < 12; i++)
        ((uint32_t*)dest)[i] = ((uint32_t*)src)[i];
    // Copy byte at offset 48
    *(uint8_t*)((uint8_t*)dest + 48) = *(uint8_t*)((uint8_t*)src + 48);
    // Copy dword at offset 52
    ((uint32_t*)dest)[13] = ((uint32_t*)src)[13];
}