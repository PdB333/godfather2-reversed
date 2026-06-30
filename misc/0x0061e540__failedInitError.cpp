// FUNC_NAME: failedInitError
int failedInitError(void)
{
    internalInitialize();   // calls initialization routine at 0x0061e4e0
    return -1;              // always returns -1 (0xFFFFFFFF) indicating failure
}