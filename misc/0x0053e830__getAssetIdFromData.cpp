// FUNC_NAME: getAssetIdFromData
int __fastcall getAssetIdFromData(void* unusedThis, int dataPointer)
{
    int result = 0;
    int buffer[3];          // local buffer, only buffer[0] used

    if (dataPointer != 0 && *(char*)(dataPointer + 0x10) != 0)  // check valid data & flag at +0x10
    {
        fillBuffer(buffer, 0x2000);   // read data chunk (0x2000 bytes)
        result = 0;
        if (buffer[0] != 0)
        {
            result = buffer[0];
        }
    }
    return result;
}