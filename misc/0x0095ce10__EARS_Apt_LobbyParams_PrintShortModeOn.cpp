// Xbox PDB: EARS_Apt_LobbyParams_PrintShortModeOn
// FUNC_NAME: MultiplayerGameModeInfo::getGameModeLocalizationKey
// Address: 0x0095ce10
// Role: Retrieves the localization key string for the current multiplayer game mode based on internal hash.

void __thiscall MultiplayerGameModeInfo::getGameModeLocalizationKey(int this, char *outBuffer)
{
    int *pManager; // pointer to global scenario manager
    uint index; // index into scenario list
    char result; // result from getCurrentGameModeIndex
    int *pScenarioEntry; // pointer to scenario entry
    int *pGameModeEntry; // pointer to game mode entry
    uint hash; // hash of game mode name

    pManager = (int *)DAT_0112b9b4; // global pointer to ScenarioManager singleton
    index = 0;
    result = getCurrentGameModeIndex(*(int *)(this + 0x10), &index); // get index from this+0x10

    if ((result != 0) && (index < *(uint *)(pManager + 2))) // check index against count at manager+8
    {
        pScenarioEntry = *(int **)(*(int *)(pManager + 1) + index * 4); // manager+4 is array of scenario pointers
        if (pScenarioEntry != 0)
        {
            pGameModeEntry = *(int **)(*(int *)(pScenarioEntry + 1) + *(int *)(this + 8) * 4); // scenarioEntry+4 is array of game mode pointers, index from this+8
            if (pGameModeEntry != 0)
            {
                hash = *(uint *)(pGameModeEntry + 0x5F); // offset 0x17c = 0x5F * 4? Actually 0x17c/4 = 0x5F, but careful: pointer arithmetic in C++ scales by sizeof(int). So pGameModeEntry + 0x5F gives offset 0x17c.
                if (hash < 0x45c2f637)
                {
                    if (hash == 0x45c2f636)
                    {
                        copyLocalizedString(outBuffer, "$mp_online_short_demolition_assault", 0x80, 0);
                        return;
                    }
                    if (hash == 0x2efecf8d)
                    {
                        copyLocalizedString(outBuffer, "$mp_online_short_team_deathmatch", 0x80, 0);
                        return;
                    }
                    if (hash == 0x3d26cff9)
                    {
                        copyLocalizedString(outBuffer, "$mp_online_short_safe_cracker", 0x80, 0);
                        return;
                    }
                }
                else if (hash == 0x7116917a)
                {
                    copyLocalizedString(outBuffer, "$mp_online_short_firestarter", 0x80, 0);
                    return;
                }
            }
        }
    }
    *outBuffer = 0; // default empty string
    return;
}