// FUNC_NAME: ConfigManager::queryGlobalSetting
void ConfigManager::queryGlobalSetting(void)
{
    // Struct used to pass a key and default values to FUN_00408a00
    struct SettingQuery {
        int key;        // +0x00 - Source: DAT_0112afb0
        int unknown1;   // +0x04 - initialized to 0
        char unknown2;  // +0x08 - initialized to 0
    } query;
    
    // Global key value (likely an integer setting ID or string pointer)
    query.key = DAT_0112afb0;
    query.unknown1 = 0;
    query.unknown2 = 0;
    
    // Call internal helper; second parameter (0) may be a default or flag
    FUN_00408a00(&query, 0);
    
    return;
}