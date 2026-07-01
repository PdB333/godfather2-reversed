// FUNC_NAME: doubleCall
// Function address: 0x008d6a10
// This function simply calls FUN_008d5e60 twice, likely for a double-buffered update or two-pass processing.

void doubleCall(void)
{
    int iVar1 = 2;
    do {
        FUN_008d5e60();   // Called twice; likely an internal update or processing function
        iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    return;
}