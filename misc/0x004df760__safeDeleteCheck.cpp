// FUNC_NAME: safeDeleteCheck
void __fastcall safeDeleteCheck(int* ptrToFlagOrPtr)
{
    // Check if the value pointed to is non-zero (e.g., a pointer or flag)
    if (*ptrToFlagOrPtr != 0)
    {
        // Call the deletion function (likely operator delete or a custom free)
        FUN_00414aa0(); // 0x00414aa0 - probably free or release function
    }
}