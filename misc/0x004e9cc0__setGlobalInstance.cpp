// FUNC_NAME: setGlobalInstance
// Address: 0x004e9cc0
// Role: Setter for a global pointer, returns previous value.
// Likely used to swap or initialize a singleton/manager instance.

uint32_t setGlobalInstance(uint32_t newValue)
{
    uint32_t oldValue = g_someGlobalPointer; // DAT_012054f8
    g_someGlobalPointer = newValue;
    return oldValue;
}