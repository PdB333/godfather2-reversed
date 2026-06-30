// FUNC_NAME: memcpy40ByteBlock
void __fastcall memcpy40ByteBlock(__int64 *src, __int64 *dstEnd, __int64 *dst)
{
    // Copies 40-byte (5 * 8) blocks from src to dst until dst reaches dstEnd.
    if (dst != dstEnd) {
        do {
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
            dst[4] = src[4];
            dst += 5;              // advance dst by 40 bytes
        } while (dst != dstEnd);
    }
}