// FUNC_NAME: copy64ByteBlock
void copy64ByteBlock(uint32_t *dest, int unused, uint32_t *src)
{
    // Copy 64 bytes (16 uint32 elements) from source to destination.
    // This is an unrolled memcpy for a fixed-size structure (e.g., matrix, transform, or packet header).
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
    dest[12] = src[12];
    dest[13] = src[13];
    dest[14] = src[14];
    dest[15] = src[15];
    // Note: param_2 (unused) is ignored.
}