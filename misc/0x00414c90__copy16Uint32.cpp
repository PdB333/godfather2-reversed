// FUNC_NAME: copy16Uint32
void copy16Uint32(unsigned int *dest, unsigned int *src)
{
    // Copy 16 dwords (64 bytes) from src to dest.
    // This is a utility function for copying fixed-size structures
    // (e.g., 4x4 matrices, quaternions, or other 16-element arrays).
    dest[0x0] = src[0x0];
    dest[0x1] = src[0x1];
    dest[0x2] = src[0x2];
    dest[0x3] = src[0x3];
    dest[0x4] = src[0x4];
    dest[0x5] = src[0x5];
    dest[0x6] = src[0x6];
    dest[0x7] = src[0x7];
    dest[0x8] = src[0x8];
    dest[0x9] = src[0x9];
    dest[0xA] = src[0xA];
    dest[0xB] = src[0xB];
    dest[0xC] = src[0xC];
    dest[0xD] = src[0xD];
    dest[0xE] = src[0xE];
    dest[0xF] = src[0xF];
}