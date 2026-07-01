// FUNC_NAME: SomeClass::checkAndHandleState
void __fastcall SomeClass::checkAndHandleState(int thisPtr)
{
    // Check if flag at +0x1028 is set, and if the value at +0xff0 is non-zero and not 0x48
    if ((*(char *)(thisPtr + 0x1028) != '\0') && 
        (*(int *)(thisPtr + 0xff0) != 0) && 
        (*(int *)(thisPtr + 0xff0) != 0x48)) 
    {
        // Call handler function at 0x007f7c00
        FUN_007f7c00();
    }
}