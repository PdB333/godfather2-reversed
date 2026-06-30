// FUNC_NAME: SettingsManager::setGlobalSetting
void __thiscall SettingsManager::setGlobalSetting(void* thisPtr, int newSetting) {
    // Check if the manager is initialized (flag at +0x28)
    if (*(char*)((int)thisPtr + 0x28) != 0) {
        // Query the global configuration state from the singleton at g_settingsState
        int state = GetConfigurationState(&g_settingsState); // FUN_00ab5130
        // If the state is valid (not -2 meaning "no change allowed")
        if (state != -2) {
            // Apply the new setting globally
            g_globalSetting = newSetting; // _DAT_0103b270
        }
    }
}