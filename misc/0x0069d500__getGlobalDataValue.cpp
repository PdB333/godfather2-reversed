// FUNC_NAME: getGlobalDataValue
// Address: 0x0069d500
// Returns a 4-byte global value (likely a singleton pointer or a configuration flag)
uint32_t getGlobalDataValue(void)
{
    return DAT_0112a024;  // Global data at 0x0112a024 – exact purpose unknown
}