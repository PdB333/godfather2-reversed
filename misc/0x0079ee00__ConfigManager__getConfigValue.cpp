// FUNC_NAME: ConfigManager::getConfigValue
void __thiscall ConfigManager::getConfigValue(int this, undefined4 *outValue1, undefined4 *outValue2)
{
    // Retrieve stored value at offset 0x2e1c (likely a member variable)
    *outValue2 = *(undefined4 *)(this + 0x2e1c);

    // Look up a configuration value by hash (0xb9140b88 corresponds to a string key)
    char found = FUN_008934e0(0xb9140b88, outValue1);
    if (found == '\0') {
        // If not found, use the global default value
        *outValue1 = DAT_00e448d8;
    }
}