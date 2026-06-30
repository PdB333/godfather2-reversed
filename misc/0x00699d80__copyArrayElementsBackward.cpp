// FUNC_NAME: copyArrayElementsBackward

void __cdecl copyArrayElementsBackward(void* pSrcArrayStart, void* pSrcArrayEnd, void* pDestArrayEnd)
{
    // Copies an array of structures, each 0x141 dwords (0x504 bytes) from the source range
    // [pSrcArrayStart, pSrcArrayEnd) to the destination range ending at pDestArrayEnd,
    // processing from the last element backward to avoid overlap issues.
    // This is used by the caller at 0x0069a140, likely a manager reallocating or duplicating
    // a contiguous block of game objects (e.g., player states or network packets).

    if (pSrcArrayEnd == pSrcArrayStart)
        return;

    do
    {
        pSrcArrayEnd = (uint32_t*)pSrcArrayEnd - 0x141;   // Move to previous element start
        pDestArrayEnd = (uint32_t*)pDestArrayEnd - 0x141; // Move destination pointer

        uint32_t* puSrc = (uint32_t*)pSrcArrayEnd;
        uint32_t* puDst = (uint32_t*)pDestArrayEnd;

        for (int iCount = 0x141; iCount != 0; iCount--)
        {
            *puDst++ = *puSrc++;
        }
    }
    while (pSrcArrayEnd != pSrcArrayStart);
}