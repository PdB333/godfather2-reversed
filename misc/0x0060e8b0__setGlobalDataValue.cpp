// FUNC_NAME: setGlobalDataValue
// Address: 0x0060e8b0
// Role: Sets a global data value (likely a flag or configuration)
void setGlobalDataValue(int value)
{
    // Global variable at 0x012058c8 - purpose unknown
    g_globalDataValue = value;
}