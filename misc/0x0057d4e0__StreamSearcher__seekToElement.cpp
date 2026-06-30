// FUNC_NAME: StreamSearcher::seekToElement
void __thiscall StreamSearcher::seekToElement(int index, unsigned char** streamPtr)
{
    unsigned char* pCurrent = *streamPtr;
    unsigned char headerByte = *pCurrent;
    unsigned char lowNibble = headerByte & 0xF;

    if (lowNibble != 5)
    {
        switch (lowNibble)
        {
        case 0:
            *streamPtr = pCurrent + 5;
            return;
        case 1:
            *streamPtr = pCurrent + 8;
            return;
        case 2:
            *streamPtr = pCurrent + 11;
            return;
        case 3:
            *streamPtr = pCurrent + 14;
            return;
        case 4:
        {
            unsigned char secondByte = pCurrent[1];
            // Skip two helper calls (likely internal stream reads)
            FUN_0057d370();
            FUN_0057d370();
            // Total size = ((secondByte << 4) | (headerByte >> 4)) * 4 + 2
            *streamPtr = pCurrent + (((unsigned int)secondByte << 4) | (headerByte >> 4)) * 4 + 2;
            return;
        }
        case 6:
            // Size = ((pCurrent[1] << 4) | (headerByte >> 4)) + 8
            *streamPtr = pCurrent + ((unsigned int)pCurrent[1] << 4 | (headerByte >> 4)) + 8;
            return;
        case 7:
            // Size = ((pCurrent[1] << 4) | (headerByte >> 4)) * 2 + 8
            *streamPtr = pCurrent + (((unsigned int)pCurrent[1] << 4 | (headerByte >> 4)) * 2) + 8;
            return;
        case 0xC:
            pCurrent += 2;
            break; // will set streamPtr below
        case 0xD:
            *streamPtr = pCurrent + 2;
            return;
        }
        *streamPtr = pCurrent;
        return;
    }

    // Type 5: List of elements. Read count and iterate.
    unsigned int count = (unsigned int)pCurrent[1] << 4 | (headerByte >> 4);
    pCurrent += 2;
    if (count != 0)
    {
        while (true)
        {
            unsigned int elementCount = (unsigned int)pCurrent[1] << 4 | (*pCurrent >> 4);
            count--;
            unsigned int typeNibble = *pCurrent & 0xF;
            if (index < (int)(elementCount - 1))
                break;
            index -= (elementCount - 1);
            // Jump to next element using type-specific size tables (base size and per-element size)
            pCurrent = pCurrent + gTypeBaseSize[typeNibble] * elementCount + gTypePerElementSize[typeNibble];
            if ((int)count < 1)
            {
                *streamPtr = pCurrent;
                return;
            }
        }
        // Found the element containing the target index; advance to its position
        unsigned char* pSub = pCurrent + 2;
        switch (typeNibble)
        {
        case 0:
            pSub = pCurrent + 5;
            break;
        case 1:
            pSub = pCurrent + 8;
            break;
        case 2:
            pSub = pCurrent + 11;
            break;
        case 3:
            pSub = pCurrent + 14;
            break;
        case 4:
            FUN_0057d370();
            FUN_0057d370();
            pSub = pSub + elementCount * 4;
            break;
        case 6:
            pSub = pCurrent + elementCount + 8;
            break;
        case 7:
            pSub = pCurrent + elementCount * 2 + 8;
            break;
        case 0xD:
            // No offset change
            break;
        }
        pCurrent = pSub;
        // Skip remaining elements in the list
        for (; 0 < (int)count; count--)
        {
            typeNibble = *pCurrent & 0xF;
            pCurrent = pCurrent + ((unsigned int)pCurrent[1] << 4 | (*pCurrent >> 4)) *
                        gTypeBaseSize[typeNibble] + gTypePerElementSize[typeNibble];
        }
    }
    *streamPtr = pCurrent;
}