// FUNC_NAME: DebugConfig::getBoolSetting
char DebugConfig::getBoolSetting(uint32_t settingId, char defaultValue) {
    char cachedValue;
    // Try to get from cache first
    if (getCachedSetting(settingId, &cachedValue) != '\0') {
        return cachedValue;
    }

    // If within valid debug context stack range, log the lookup
    if ((g_currentContextIndex >= 0) &&
        (g_currentContextIndex < (g_contextStackEnd - g_contextStackStart) / 4)) {
        debugStartSettingLookup(settingId); // FUN_004d3bc0
        const char* valueStr = (defaultValue != '\0') ? "true" : "false";
        // Push a debug context scope (likely for nesting/log grouping)
        // The stack array local_10 holds context data; local_4 is a function pointer
        // that gets set by pushDebugContextScope
        debugContextStack local_10; // struct with callback info
        pushDebugContextScope(&local_10); // FUN_0069b380
        debugOutputString(valueStr);      // FUN_004d3d90
        // Invoke the context's callback if present
        if (local_10.callbackPtr != NULL) {
            local_10.callbackPtr(local_10.callbackData);
        }
    }

    return defaultValue;
}