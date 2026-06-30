// FUNC_NAME: ConfigManager::applyConfig
void ConfigManager::applyConfig(uint32_t* configData) {
    // Copy configuration fields from packed data to global state
    // +0x00: first config field
    g_configField1 = configData[0];
    // +0x08: third config field (index 2)
    g_configField2 = configData[2];
    // +0x10: fixed value from global constant (0x00e447a4)
    g_configField3 = g_constantValue; // DAT_00e447a4
    // +0x24: tenth config field (index 9)
    g_configField4 = configData[9];
    // +0x28: eleventh config field (index 10)
    g_configField5 = configData[10];

    // Initialize core subsystems after applying configuration
    FUN_0089e200(); // e.g., GamePlaySystem::init()
    FUN_0089e240(); // e.g., AudioManager::init()
}