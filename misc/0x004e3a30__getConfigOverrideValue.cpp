// FUNC_NAME: getConfigOverrideValue
int getConfigOverrideValue(void)
{
    // Global pointer to an object (likely a singleton configuration manager)
    // If non-null, read a value at offset 0x16c from it
    if (g_pConfigManager != nullptr) {
        // +0x16c: integer override value (e.g., a game setting)
        return *(int *)((char *)g_pConfigManager + 0x16c);
    }
    // Fallback default value stored in a global variable
    return g_defaultConfigValue;
}