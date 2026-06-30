// FUNC_NAME: copyGameStruct
void __fastcall copyGameStruct(uint32_t* dest, const uint32_t* src) {
    // Copy 12 dwords (offsets 0-47)
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = src[3];
    dest[4] = src[4];
    dest[5] = src[5];
    dest[6] = src[6];
    dest[7] = src[7];
    dest[8] = src[8];
    dest[9] = src[9];
    dest[10] = src[10];
    dest[11] = src[11];

    // Copy single byte at offset 48 (start of 13th dword)
    *(uint8_t*)(dest + 0xC) = *(const uint8_t*)(src + 0xC);

    // Copy 14th dword at offset 52
    dest[13] = src[13];
}