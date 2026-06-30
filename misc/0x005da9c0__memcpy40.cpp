// FUNC_NAME: memcpy40
void __fastcall memcpy40(void* dst, const void* src, const void* srcEnd)
{
    // Copy 40-byte chunks (5 * 8) from src to dst until src reaches srcEnd
    uint64* dst64 = (uint64*)dst;
    const uint64* src64 = (const uint64*)src;
    const uint64* end64 = (const uint64*)srcEnd;

    if (src64 != end64) {
        do {
            dst64[0] = src64[0];
            dst64[1] = src64[1];
            dst64[2] = src64[2];
            dst64[3] = src64[3];
            dst64[4] = src64[4];
            src64 += 5;
            dst64 += 5;
        } while (src64 != end64);
    }
}