// FUNC_NAME: conditionalLogBuffer
void conditionalLogBuffer(void* thisPtr, int inputData)
{
    char buffer[12];
    int unused1 = 0;
    int unused2 = 0;
    int unused3 = 0;
    int unused4 = DAT_00e2b1a4;
    char cond = FUN_00577f40();
    if (cond != '\0') {
        FUN_0044b4e0(inputData, buffer);
    }
    return;
}