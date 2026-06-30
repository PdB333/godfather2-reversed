// FUNC_NAME: getIsDebugMode
// Function address: 0x0069d530
// Returns a global 2-byte flag (likely debug mode or demo status).
unsigned short getIsDebugMode(void)
{
    // DAT_0112a03c -> global flag variable
    return g_isDebugMode;
}