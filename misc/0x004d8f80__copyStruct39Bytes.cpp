// FUNC_NAME: copyStruct39Bytes
void __fastcall copyStruct39Bytes(void* dst, void* src)
{
    if (dst != src)
    {
        // Copy 9 dwords (36 bytes)
        for (int i = 9; i != 0; i--)
        {
            *(unsigned int*)dst = *(unsigned int*)src;
            dst = (char*)dst + 4;
            src = (char*)src + 4;
        }
        // Copy remaining 3 bytes: a short and a byte
        *(unsigned short*)dst = *(unsigned short*)src;
        *((char*)dst + 2) = *((char*)src + 2);
    }
}