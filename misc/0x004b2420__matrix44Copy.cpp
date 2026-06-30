// FUNC_NAME: matrix44Copy
void matrix44Copy(void* dest, void* src) {
    // Copies a 4x4 matrix (16 floats) from source at offset 0x1c to destination.
    // Offsets in source: 0x1c, 0x20, 0x24, 0x28 (row0)
    //                    0x2c, 0x30, 0x34, 0x38 (row1)
    //                    0x3c, 0x40, 0x44, 0x48 (row2)
    //                    0x4c, 0x50, 0x54, 0x58 (row3)
    typedef __m128 float4; // or just use uint32_t for raw copy
    uint32_t* d = (uint32_t*)dest;
    uint32_t* s = (uint32_t*)((char*)src + 0x1c);

    // Row 0
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    d[3] = s[3];
    // Row 1
    d[4] = s[4];
    d[5] = s[5];
    d[6] = s[6];
    d[7] = s[7];
    // Row 2
    d[8] = s[8];
    d[9] = s[9];
    d[10] = s[10];
    d[11] = s[11];
    // Row 3
    d[12] = s[12];
    d[13] = s[13];
    d[14] = s[14];
    d[15] = s[15];
}