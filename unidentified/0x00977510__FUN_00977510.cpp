// FUNC_NAME: UnknownClass::getData
bool __thiscall UnknownClass::getData(int thisPtr, int* outData) // outData is pointer to 3 ints (12 bytes)
{
    bool hasData = *(int*)(thisPtr + 0xf8) != 0;
    if (hasData)
    {
        char buffer[48]; // filled by FUN_004df780
        FUN_004df780(buffer); // fills buffer with some data
        // Copy 12 bytes from buffer offset 0x30 into outData[0..2]
        outData[0] = *(int*)(buffer + 0x30); // local_20
        outData[1] = *(int*)(buffer + 0x34); // uStack_1c
        outData[2] = *(int*)(buffer + 0x38); // uStack_18
        // outData[3] is left unchanged (original value preserved)
    }
    return hasData;
}