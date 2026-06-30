// FUNC_NAME: GameConfigManager::setConfigObject
void __thiscall GameConfigManager::setConfigObject(GameConfigManager* this, ConfigProvider* pConfig)
{
    // Check if config provider is valid and we haven't already assigned one
    if ((pConfig != (ConfigProvider *)0x0) && (*(int *)(this + 0xc) == 0)) {
        // Get the GameID string from the config provider (virtual function at vtable+0x4c)
        wchar_t *gameId = (wchar_t *)(**(code **)(*pConfig + 0x4c))(L"GameID");
        if (gameId != (wchar_t *)0x0) {
            wchar_t *expectedId = (wchar_t *)(*(int *)(this + 0x10)); // +0x10: expected GameID
            if (expectedId == (wchar_t *)0x0) {
                expectedId = (wchar_t *)&DAT_0120546e; // default empty wide string
            }
            // Compare wide strings (character-by-character, 2 bytes each)
            int cmp;
            wchar_t *p1 = gameId;
            wchar_t *p2 = expectedId;
            do {
                wchar_t c1 = *p1;
                wchar_t c2 = *p2;
                if (c1 != c2) {
                    cmp = (c1 < c2) ? -1 : 1;
                    break;
                }
                if (c1 == 0) {
                    cmp = 0;
                    break;
                }
                p1++;
                p2++;
            } while (true);
            // If GameIDs match, also check GameConfiguration exists and store provider
            if (cmp == 0) {
                void *gameConfig = (void *)(**(code **)(*pConfig + 0x4c))(L"GameConfiguration");
                if (gameConfig != (void *)0x0) {
                    *(ConfigProvider **)(this + 0xc) = pConfig; // +0x0c: stored config provider
                }
            }
        }
    }
}