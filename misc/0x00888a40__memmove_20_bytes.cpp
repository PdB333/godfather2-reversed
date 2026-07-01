// FUNC_NAME: memmove_20_bytes
void memmove_20_bytes(uint* dst, uint* src, uint* end)
{
    uint* currentDst;
    int count;
    uint* currentSrc;
    
    if (dst != src) {
        do {
            currentDst = dst + 0x14;
            currentSrc = end;
            for (count = 0x14; count != 0; count = count + -1) {
                *dst = *currentSrc;
                currentSrc = currentSrc + 1;
                dst = dst + 1;
            }
            dst = currentDst;
        } while (currentDst != src);
    }
    return;
}