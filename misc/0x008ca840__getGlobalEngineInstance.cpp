// FUNC_NAME: getGlobalEngineInstance
uint32_t getGlobalEngineInstance(void)
{
    // Return the global singleton pointer stored at 0x00e544f8
    // This is likely a pointer to a manager or engine state instance.
    return DAT_00e544f8;
}