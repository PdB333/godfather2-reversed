//FUNC_NAME: getTlsOffsetValue
int __fastcall getTlsOffsetValue(int *offsetPtr)
{
    int result = 0;
    if (*offsetPtr != 0)
    {
        // Access thread-local storage: FS:[0x2C] points to TLS array
        // First TLS slot (index 0) contains a pointer to per-module TLS data
        // Offset 8 into that data is some base value
        int *tlsArray = (int *)__readfsdword(0x2C);
        int *tlsData = (int *)*tlsArray;
        int baseValue = *(int *)((char *)tlsData + 8);
        result = baseValue + *offsetPtr;
    }
    return result;
}