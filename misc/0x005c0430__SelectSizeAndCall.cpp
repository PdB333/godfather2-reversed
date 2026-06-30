// FUNC_NAME: SelectSizeAndCall
void SelectSizeAndCall(void* param1, void* param2, void* param3, void* param4, void* param5, char flag)
{
    // If flag is non-zero, size = 6; else size = 3.
    int size = (-(flag != '\0') & 3U) + 3;  // Equivalent to: (flag ? 6 : 3)
    InternalFunction(param1, param2, size, param3, param4, param5);
}