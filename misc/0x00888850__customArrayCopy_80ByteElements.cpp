// FUNC_NAME: customArrayCopy_80ByteElements
void customArrayCopy_80ByteElements(uint32_t** outDestEnd, uint32_t* srcStart, uint32_t* srcEnd, uint32_t* destStart)
{
    *outDestEnd = destStart;
    while (srcStart != srcEnd)
    {
        if (destStart != 0)
        {
            // Copy 20 uint32_t (80 bytes) per element
            for (int i = 0; i < 20; i++)
            {
                destStart[i] = srcStart[i];
            }
        }
        srcStart += 20;   // advance by 20 * 4 = 80 bytes
        destStart += 20;  // advance by 20 * 4 = 80 bytes
    }
    *outDestEnd = destStart;
}