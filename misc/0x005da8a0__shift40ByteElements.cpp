// FUNC_NAME: shift40ByteElements
// 0x005da8a0: Shifts 40-byte elements from src to dst until dst reaches dstEnd.
// Used internally to compact a circular buffer or queue of fixed-size (40-byte) entries.
void __fastcall shift40ByteElements(void* src, void* dstEnd, void* dst)
{
    typedef uint64_t Element40Bytes[5]; // 5 qwords = 40 bytes
    Element40Bytes* pSrc = (Element40Bytes*)src;
    Element40Bytes* pDst = (Element40Bytes*)dst;
    Element40Bytes* pDstEnd = (Element40Bytes*)dstEnd;

    // Only shift if there is at least one element to move
    if (pDst != pDstEnd)
    {
        do
        {
            // Copy one 40-byte element (5 qwords) from source to destination
            (*pDst)[0] = (*pSrc)[0];
            (*pDst)[1] = (*pSrc)[1];
            (*pDst)[2] = (*pSrc)[2];
            (*pDst)[3] = (*pSrc)[3];
            (*pDst)[4] = (*pSrc)[4];

            pSrc++;
            pDst++;
        } while (pDst != pDstEnd);
    }
}