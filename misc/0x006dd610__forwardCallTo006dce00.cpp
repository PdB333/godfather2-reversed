// FUNC_NAME: forwardCallTo006dce00
// This function simply delegates to the function at 0x006dce00.
// It is called from two locations (0x007da480 and 0x007c5f60), suggesting it may be a common initialization wrapper.
void forwardCallTo006dce00(void)
{
    FUN_006dce00();
    return;
}