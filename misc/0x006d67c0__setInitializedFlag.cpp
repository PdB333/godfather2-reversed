// FUNC_NAME: setInitializedFlag

void __fastcall setInitializedFlag(int thisPtr)
{
    // +0x228 is a flag that, once set to 1, prevents re-initialization
    int* flag = (int*)(thisPtr + 0x228);
    if (*flag == 0)
    {
        *flag = 1;
    }
}