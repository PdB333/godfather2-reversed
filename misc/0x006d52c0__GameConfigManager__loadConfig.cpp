// FUNC_NAME: GameConfigManager::loadConfig
void __cdecl GameConfigManager::loadConfig(uint32_t *configData)
{
    // Store configuration values from the provided data structure
    g_configScreenWidth  = configData[0];       // +0x00: screen width
    g_configScreenHeight = configData[2];       // +0x08: screen height (uint32_t aligned)
    g_configFrameRate    = DAT_00e447a4;         // Global frame rate setting
    g_configSoundVolume  = configData[9];       // +0x24: sound volume
    g_configMusicVolume  = configData[10];      // +0x28: music volume

    // Initialize video and audio subsystems with the new config
    initVideoSettings();   // FUN_0089e200
    initAudioSettings();   // FUN_0089e240
}