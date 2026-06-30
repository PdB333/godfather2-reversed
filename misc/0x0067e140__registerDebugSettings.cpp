// FUNC_NAME: registerDebugSettings
void registerDebugSettings(void)
{
    // Register debug settings with hashed keys using a settings registry function.
    // Each call registers a boolean/float/int setting.
    unsigned int timestamp = getTimestamp(); // FUN_009c89c0 might return current tick or random
    registerSetting(0x5393ac01, timestamp); // Possibly hashed "debugDraw" or similar
    timestamp = getTimestamp();
    registerSetting(0x9dc401b7, timestamp); // "showFPS" etc.
    timestamp = getTimestampAlt(); // thunk_FUN_009c9730 might be a slightly different version
    registerSetting(0x7a10372b, timestamp);
    timestamp = getTimestamp();
    registerSetting(0x38b2b8d2, timestamp);
    timestamp = getTimestamp();
    registerSetting(0x67a6002e, timestamp);
    return;
}