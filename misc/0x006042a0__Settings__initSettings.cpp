// FUNC_NAME: Settings::initSettings
void __thiscall Settings::initSettings(DataStore* dataStore, const char* value1, const char* value2)
{
    baseInit(); // FUN_00603bf0
    debugPrint(0x1f); // FUN_004d3fe0
    dataStore->setString(g_keyResourceName, value1); // FUN_004d4ad0, key at 0x00e325c4
    m_settingsContainer.init(); // FUN_004d4300, subobject at this+0xa4
    dataStore->setString(g_keyResourceType, value2); // FUN_004d4b00, key at 0x00e4086c
}