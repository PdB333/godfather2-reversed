// FUNC_NAME: copyQuaternionAndZeroTranslation
// Function address: 0x00883210
// Copies 4 dwords (likely a quaternion) from src to dst, then zeros the next 3 dwords (likely translation vector).
void copyQuaternionAndZeroTranslation(uint32_t* src, uint32_t* dst)
{
    // Copy 4 dwords (quaternion: x, y, z, w)
    uint32_t v0 = src[0];
    uint32_t v1 = src[1];
    uint32_t v2 = src[2];
    uint32_t v3 = src[3];
    dst[0] = v0;
    dst[1] = v1;
    dst[2] = v2;
    dst[3] = v3;

    // Zero out next 3 dwords (translation: x, y, z)
    dst[4] = 0;
    dst[5] = 0;
    dst[6] = 0;
}