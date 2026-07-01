// FUNC_NAME: ConfigManager::trySetConfiguration
// Function address: 0x00567b10
// Role: Checks if the given config provider has a matching game ID and contains a game configuration;
// if so, stores the provider pointer into the member variable at +0x0c.

void __thiscall ConfigManager::trySetConfiguration(int thisPtr, int* pConfigProvider)
{
    byte bVar1;
    wchar_t* pGameID;
    int iVar3;
    wchar_t* pExpectedID;
    bool bVar5;

    // Only proceed if provider is valid and no configuration has been set yet.
    if ((pConfigProvider != nullptr) && (*(int*)(thisPtr + 0x0c) == 0)) {
        // Retrieve the "GameID" string from the provider via a virtual function call (vtable+0x4c).
        pGameID = (wchar_t*)(**(code**)(*pConfigProvider + 0x4c))("GameID");
        if (pGameID != nullptr) {
            pExpectedID = *(wchar_t**)(thisPtr + 0x10);
            if (pExpectedID == nullptr) {
                pExpectedID = (wchar_t*)&DAT_0120546e; // Default fallback string
            }
            // Compare wide strings character by character (2 bytes each).
            do {
                bVar1 = *pGameID;
                bVar5 = bVar1 < *pExpectedID;
                if (bVar1 != *pExpectedID) {
                    iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
                    goto COMPARE_DONE;
                }
                if (bVar1 == 0) break;
                bVar1 = pGameID[1];
                bVar5 = bVar1 < pExpectedID[1];
                if (bVar1 != pExpectedID[1]) {
                    iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
                    goto COMPARE_DONE;
                }
                pGameID += 2;       // Move to next wide character (2 bytes)
                pExpectedID += 2;
            } while (bVar1 != 0);
            iVar3 = 0;  // Strings are equal

COMPARE_DONE:
            // If game IDs match, check that the provider also has a "GameConfiguration".
            if (iVar3 == 0) {
                iVar3 = (**(code**)(*pConfigProvider + 0x4c))("GameConfiguration");
                if (iVar3 != 0) {
                    *(int**)(thisPtr + 0x0c) = pConfigProvider;  // +0x0c: m_pConfigProvider
                }
            }
        }
    }
    return;
}