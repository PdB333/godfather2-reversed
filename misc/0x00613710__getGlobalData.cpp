// FUNC_NAME: getGlobalData
// Address: 0x00613710
// Role: Returns a pointer to a global data buffer (DAT_011f6a30). Likely a singleton or static storage.

void* getGlobalData(void)
{
    // Return address of global data structure
    return &g_someGlobalData;
}