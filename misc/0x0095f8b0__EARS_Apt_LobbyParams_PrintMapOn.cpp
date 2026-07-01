// Xbox PDB: EARS_Apt_LobbyParams_PrintMapOn
// FUNC_NAME: MultiplayerDLCMapManager::getSelectedMapInfo
void __thiscall MultiplayerDLCMapManager::getSelectedMapInfo(int this, char* mapNameBuffer, char* helpTextBuffer)
{
    // Global indicating if online/DLC content is available
    extern bool g_isOnlineOrDLCAvailable; // DAT_0112b9b4
    // Array of DLC map definitions (size 0x20 each)
    extern DLCMapEntry* g_dlcMapEntries; // DAT_0113081c
    // Default empty string for missing entries
    extern const char* g_emptyString; // DAT_0120546e (likely "")

    // Likely lock or synchronization call
    FUN_0095ecd0();

    char* bufferPtr = mapNameBuffer;
    *mapNameBuffer = '\0';

    if (g_isOnlineOrDLCAvailable)
    {
        int mapIndex;
        bool hasMap = FUN_0095c8c0(*(int*)(this + 0x10), &mapIndex);

        if (!hasMap)
        {
            // No specific DLC map selected; use default localization keys
            copyLocalizedString(bufferPtr, "$mp_online_pdlc_map", 0x80, 0);
            if (helpTextBuffer)
            {
                copyLocalizedString(bufferPtr, "$mp_online_pdlc_map_helptext", 0x80, 0);
            }
        }
        else
        {
            // Index of the selected DLC map
            DLCMapEntry* entry = (DLCMapEntry*)((int)g_dlcMapEntries + mapIndex * 0x20);
            const char* mapName = entry->mapNamePtr;
            if (mapName == nullptr)
            {
                mapName = g_emptyString;
            }
            copyLocalizedString(bufferPtr, mapName, 0x80, entry->mapNameId);

            if (helpTextBuffer)
            {
                const char* helpText = entry->helpTextPtr; // +0x10
                if (helpText == nullptr)
                {
                    helpText = g_emptyString;
                }
                copyLocalizedString(helpTextBuffer, helpText, 0x80, entry->helpTextId); // +0x14
            }
        }
    }
}