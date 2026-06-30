// FUNC_NAME: gameQueryFlagFromType
unsigned char __cdecl gameQueryFlagFromType(unsigned char type, unsigned int extraParam, int index)
{
    unsigned char stackBuffer[3]; // [esp+0x07] - 3-byte local array, uninitialized in decompiled code
    unsigned int temp = extraParam; // Assigned but not used in decompiled logic

    if (type != 0x01 && type != 0x03) {
        return 0xFF;
    }
    return stackBuffer[index]; // Returns value from uninitialized stack; likely a decompilation artifact
}