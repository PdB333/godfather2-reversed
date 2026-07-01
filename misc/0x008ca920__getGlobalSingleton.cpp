// FUNC_NAME: getGlobalSingleton
// FUNCTION_ADDRESS: 0x008ca920
// ROLE: Returns a global singleton pointer stored at DAT_00e54508. Likely a getter for a manager instance.
uint32_t getGlobalSingleton()
{
    return gGlobalSingleton; // DAT_00e54508 - global singleton pointer
}