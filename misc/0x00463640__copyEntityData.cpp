// FUNC_NAME: copyEntityData
uint32_t* copyEntityData(uint32_t* dest, uint32_t* src) {
    // Copy first six fields (offsets 0x00, 0x04, 0x08, 0x0C, 0x10, 0x14)
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = src[3];
    dest[4] = src[4];
    dest[5] = src[5];

    // Internal post-copy initialization (unknown purpose)
    postCopyInitialization(); // FUN_00463730

    // Copy field at offset 0x24 (9th dword)
    dest[9] = src[9];

    return dest;
}