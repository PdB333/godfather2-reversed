// FUNC_NAME: GodfatherGameManager::GetSetting
int GodfatherGameManager::GetSetting(int isEnabled) {
    if (isEnabled) {
        // DAT_01131018 likely points to a global manager instance (e.g., settings/state block)
        // FUN_0043b870 retrieves a value from that manager
        return GetGlobalSetting(DAT_01131018);
    }
    return 0;
}