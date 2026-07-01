// Xbox PDB: EARS_Apt_LobbyParams_PrintNameOn
// FUNC_NAME: MultiplayerOptionsManager::getOptionDescription
void __thiscall MultiplayerOptionsManager::getOptionDescription(int *this, int optionId, char *descriptionBuffer, char *helpBuffer) {
    int *entryPtr;
    int index;
    char *stringPtr;
    char *tempString;
    int tempInt;
    // Local variables for cleanup
    char *localString;
    int localInt1, localInt2;
    code *cleanupFunc;

    // Call some initialization function
    FUN_0095ecd0();

    // Initialize output buffer
    *descriptionBuffer = 0;

    switch (optionId) {
    case 0: { // Game type or map?
        // this[0] is the index for some array at DAT_01130834, each entry is 0x20 bytes
        entryPtr = (int *)(this[0] * 0x20 + DAT_01130834);
        stringPtr = (char *)*entryPtr;
        if (stringPtr == (char *)0x0) {
            stringPtr = &DAT_0120546e; // Empty string placeholder
        }
        // Copy localized string into descriptionBuffer with max length 0x80
        FUN_005c4660(descriptionBuffer, stringPtr, 0x80, entryPtr[1]); // entryPtr[1] is probably category or flags
        if (helpBuffer != 0) {
            index = this[0] * 0x20 + DAT_01130834;
            stringPtr = *(char **)(index + 0x10); // offset 0x10 in entry
            if (stringPtr == (char *)0x0) {
                stringPtr = &DAT_0120546e;
            }
            FUN_005c4660(helpBuffer, stringPtr, 0x80, *(int *)(index + 0x14));
        }
        break;
    }
    case 1: { // Map description
        FUN_0095f8b0(descriptionBuffer, helpBuffer);
        return;
    }
    case 2: { // Plasma waiting? (Game mode selection)
        if (DAT_011307fc == 0) {
            FUN_005c4660(descriptionBuffer, "$fe_plasma_waiting", 0x80, 0);
            return;
        }
        if ((uint)this[2] < DAT_011307fc) {
            localString = (char *)0x0;
            localInt1 = 0;
            localInt2 = 0;
            cleanupFunc = (code *)0x0;
            // Fetch string for selected game mode
            FUN_00603330(*(int *)(DAT_011307f8 + this[2] * 8), &localString);
            stringPtr = localString;
            if (localString == (char *)0x0) {
                stringPtr = &DAT_0120546e;
            }
            FUN_005c4660(descriptionBuffer, stringPtr, 0x80, localInt1);
            if (helpBuffer != 0) {
                // Fetch help string
                FUN_00603330(*(int *)(DAT_011307f8 + 4 + this[2] * 8), &localString);
                stringPtr = localString;
                if (localString == (char *)0x0) {
                    stringPtr = &DAT_0120546e;
                }
                FUN_005c4660(helpBuffer, stringPtr, 0x80, localInt1);
            }
            if (localString != (char *)0x0) {
                (*cleanupFunc)(localString); // Release string
            }
        }
        break;
    }
    case 3: { // Score limit
        localString = (char *)0x0;
        localInt1 = 0;
        localInt2 = 0;
        cleanupFunc = (code *)0x0;
        FUN_00603d30(this[0xd], &localString, 1); // this[0xd] is offset 0x34? Actually 0xd*4 = 0x34
        stringPtr = localString;
        if (localString == (char *)0x0) {
            stringPtr = &DAT_0120546e;
        }
        FUN_005c4660(descriptionBuffer, stringPtr, 0x80, localInt1);
        if (helpBuffer != 0) {
            FUN_005c4660(helpBuffer, "$mp_score_limit_help", 0x80, 0);
        }
        if (localString != (char *)0x0) {
            (*cleanupFunc)(localString);
        }
        break;
    }
    case 4: { // Time limit
        if ((uint)this[9] < DAT_01130850) {
            entryPtr = (int *)(this[9] * 0x10 + DAT_0113084c);
            stringPtr = (char *)*entryPtr;
            if (stringPtr == (char *)0x0) {
                stringPtr = &DAT_0120546e;
            }
            FUN_005c4660(descriptionBuffer, stringPtr, 0x80, entryPtr[1]);
            if (helpBuffer != 0) {
                FUN_005c4660(helpBuffer, "$mp_time_limit_help", 0x80, 0);
            }
        }
        break;
    }
    case 5: { // Max players
        if ((uint)this[10] < DAT_0113082c) {
            entryPtr = (int *)(this[10] * 0x10 + DAT_01130828);
            stringPtr = (char *)*entryPtr;
            if (stringPtr == (char *)0x0) {
                stringPtr = &DAT_0120546e;
            }
            FUN_005c4660(descriptionBuffer, stringPtr, 0x80, entryPtr[1]);
            if (helpBuffer != 0) {
                FUN_005c4660(helpBuffer, "$mp_max_players_help", 0x80, 0);
            }
        }
        break;
    }
    case 6: { // Max rank
        if ((uint)this[5] < DAT_01130808) {
            entryPtr = (int *)(this[5] * 0x10 + DAT_01130804);
            stringPtr = (char *)*entryPtr;
            if (stringPtr == (char *)0x0) {
                stringPtr = &DAT_0120546e;
            }
            FUN_005c4660(descriptionBuffer, stringPtr, 0x80, entryPtr[1]);
            if (helpBuffer != 0) {
                FUN_005c4660(helpBuffer, "$mp_max_rank_help", 0x80, 0);
            }
        }
        break;
    }
    case 7: { // Respawn time
        if ((uint)this[8] < DAT_01130814) {
            entryPtr = (int *)(this[8] * 0x10 + DAT_01130810);
            stringPtr = (char *)*entryPtr;
            if (stringPtr == (char *)0x0) {
                stringPtr = &DAT_0120546e;
            }
            FUN_005c4660(descriptionBuffer, stringPtr, 0x80, entryPtr[1]);
            if (helpBuffer != 0) {
                FUN_005c4660(helpBuffer, "$mp_respawn_time_help", 0x80, 0);
            }
        }
        break;
    }
    case 8: { // Team balance toggle
        if (*(char *)((int)this + 0x7a) == '\0') {
            stringPtr = "$mp_online_team_balance_off";
        } else {
            stringPtr = "$mp_online_team_balance_on";
        }
        FUN_005c4660(descriptionBuffer, stringPtr, 0x80, 0);
        if (helpBuffer != 0) {
            FUN_005c4660(helpBuffer, "$mp_balance_teams_help", 0x80, 0);
        }
        break;
    }
    case 9: { // Winning cut? (score to win)
        if ((uint)this[7] < DAT_01130844) {
            entryPtr = (int *)(this[7] * 0x10 + DAT_01130840);
            stringPtr = (char *)*entryPtr;
            if (stringPtr == (char *)0x0) {
                stringPtr = &DAT_0120546e;
            }
            FUN_005c4660(descriptionBuffer, stringPtr, 0x80, entryPtr[1]);
            if (helpBuffer != 0) {
                FUN_005c4660(helpBuffer, "$mp_winning_cut", 0x80, 0);
            }
        }
        break;
    }
    }
    return;
}